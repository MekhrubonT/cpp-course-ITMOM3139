#ifndef EITHER_H
#define EITHER_H

#include <type_traits>
#include <algorithm>
#include <memory>
#include <bits/stdc++.h>

namespace either_m {
	enum type_t { LEFT, RIGHT, LEFT_H, RIGHT_H};

	type_t get_base(const type_t& cur) {
		switch (cur) {
			case LEFT_H: return  LEFT;
			case RIGHT_H: return RIGHT;
			default: return cur;
		}
	}

	type_t heap(const type_t& cur) {
		assert(cur != LEFT_H && cur != RIGHT_H);
		return cur == LEFT ? LEFT_H : RIGHT_H;
	}

	bool is_heap(const type_t& cur) {
		return cur == LEFT_H || cur == RIGHT_H;
	}

	struct emplace_left_t {};
	static emplace_left_t emplace_left;

	struct emplace_right_t {};
	static emplace_right_t emplace_right;

	// Left != Right
	template<typename Left, typename Right>
	struct either {
		either(Left arg) : type(LEFT) {
			new (&data) Left(arg);
		}
		either(Right arg) : type(RIGHT) {
			new (&data) Right(arg);
		}

		either(either const& other) : type(get_base(other.type)) {
			if (other.is_left()) {
				new (&data) Left(std::forward<const Left&>(other.left()));
			} else {
				new (&data) Right(std::forward<const Right&>(other.right()));
			}
		}
		either(either&& other) : type(get_base(other.type)) {
			if (other.is_left()) {
				new (&data) Left(std::forward<Left&&>(other.left()));
			} else {
				new (&data) Right(std::forward<Right&&>(other.right()));
			}
		}

		void clear_data() {
			if (type == LEFT) {
				reinterpret_cast<Left*>(&data)->~Left();
			} else if (type == RIGHT) {
				reinterpret_cast<Right*>(&data)->~Right();
			} else if (type == LEFT_H) {
				reinterpret_cast<std::unique_ptr<Left>*>(&data)->~unique_ptr();
			} else {
				reinterpret_cast<std::unique_ptr<Right>*>(&data)->~unique_ptr();
			}
		}

		~either() {
			clear_data();
		}

		either& operator=(either other) {
			if (other.is_left())
				emplace(emplace_left, other.left());
			else 
				emplace(emplace_right, other.right());
			return *this;	
		} 

		bool is_left() const {
			return get_base(type) == LEFT;
		}
		Left& left() {
			if (type == LEFT)
				return *reinterpret_cast<Left*>(&data);
			return **reinterpret_cast<std::unique_ptr<Left>*>(&data);
		}
		Left const& left() const {
			if (type == LEFT)
				return *reinterpret_cast<Left const*>(&data);
			return **reinterpret_cast<std::unique_ptr<const Left> const*>(&data);
		}

		bool is_right() const {
			return get_base(type) == RIGHT;
		}
		Right& right() {
			if (type == RIGHT)
				return *reinterpret_cast<Right*>(&data);
			return **reinterpret_cast<std::unique_ptr<Right>*>(&data);
		}
		Right const& right() const {
			if (type == RIGHT)
				return *reinterpret_cast<Right const*>(&data);
			return **reinterpret_cast<std::unique_ptr<Right const> const*>(&data);
		}



		template<typename... Args>
		void emplace(emplace_left_t, Args&&... args) {
			if (std::is_nothrow_constructible<Left, Args...>::value) {
				emplace<Left>(std::forward<Args>(args)...);
				type = LEFT;
			} else if (type == LEFT) {
				emplaceHeap<Left>(left(), LEFT, args...);
			} else {
				emplaceHeap<Left>(right(), LEFT, args...);				
			}
		}
		
		template<typename... Args>
		either(emplace_left_t, Args&&... args) : type(LEFT) {
			new (&data) Left(std::forward<Args>(args)...);
		}


		template<typename... Args>
		void emplace(emplace_right_t, Args&&... args) {
			if (std::is_nothrow_constructible<Right, Args...>::value || is_heap(type)) {
				emplace<Right>(std::forward<Args>(args)...);
				type = RIGHT;
			} else if (type == LEFT) {
				emplaceHeap<Right>(left(), RIGHT, std::forward<Args>(args)...);
			} else {
				emplaceHeap<Right>(right(), RIGHT, std::forward<Args>(args)...);				
			}
		}

		template<typename... Args>
		either(emplace_right_t, Args&&... args) : type(RIGHT) {
			new (&data) Right(std::forward<Args>(args)...);
		} 

private:

		template<typename SLeft, typename SRight, typename Rlhs, typename Rrhs> 
		friend void swapImpl(either<SLeft, SRight> &lhs, either<SLeft, SRight> &rhs,
				const Rlhs ldata, const Rrhs rdata,
				type_t const& ltype, type_t const& rtype);

		template<typename Type, typename... Args>
		void emplace(Args&&... args) {
			clear_data();
			new (&data) Type(std::forward<Args>(args)...);
		}	

		template<typename NType, typename Type, typename... Args>
		void emplaceHeap (Type old, type_t newType, Args&&... args) {
			auto tmp = std::make_unique<Type>(old);
			try {
				clear_data();
				new (&data) NType(std::forward<Args> (args)...);					
				type = newType;
			} catch (std::exception e) {
				type = heap(newType);
				new (&data) std::unique_ptr<Type>(tmp.release());
				throw;
			}	
		}


		typedef typename std::aligned_storage<std::max({sizeof(std::unique_ptr<Left>), sizeof(Left), sizeof(Right)}), 
								std::max({alignof(std::unique_ptr<Left>), alignof(Left), alignof(Right)})>::type
								data_t;
		type_t type;
		data_t data;	
	};




	template<typename F, typename Left, typename Right, typename Res, typename Args>
	auto apply(F const& f, either<Left, Right> const& cur) {
		if (cur.is_left()) {
			return f(cur.left());
		} else {
			return f(cur.right());			
		}
	}
	template<typename F, typename Left, typename Right>
	auto apply(F const& f, either<Left, Right> cur) {
		if (cur.is_left()) {
			return f(cur.left());
		} else {
			return f(cur.right());			
		}
	}

	template<typename Left, typename Right, typename Rlhs, typename Rrhs> 
	void swapImpl(either<Left, Right> &lhs, either<Left, Right> &rhs,
		const Rlhs ldata, const Rrhs rdata,
		type_t const& ltype, type_t const& rtype) {

		try {
			lhs.clear_data();
			new (&lhs.data) Rrhs(rdata);
			lhs.type = rtype;
			rhs.clear_data();
			new (&rhs.data) Rlhs(ldata);
			rhs.type = ltype;
		} catch (std::exception e){
			lhs.type = heap(ltype);
			rhs.type = heap(rtype);
			new (&lhs.data) std::unique_ptr<Rlhs>(std::make_unique<Rlhs>(ldata));
			new (&rhs.data) std::unique_ptr<Rrhs>(std::make_unique<Rrhs>(rdata));
			throw;
		}
	}

	template<typename Left, typename Right>	
	void swap(either<Left, Right> &lhs, either<Left, Right> &rhs) {
		if (lhs.is_left() && rhs.is_left()) {
			swapImpl(lhs, rhs, lhs.left(), rhs.left(), LEFT, LEFT);
		} else if (lhs.is_right() && rhs.is_left()) {
			swapImpl(lhs, rhs, lhs.right(), rhs.left(), RIGHT, LEFT);
		} else if (lhs.is_left() && rhs.is_right()) {
			swapImpl(lhs, rhs, lhs.left(), rhs.right(), LEFT, RIGHT);
		} else {
			swapImpl(lhs, rhs, lhs.right(), rhs.right(), RIGHT, RIGHT);
		}
	}

	template<typename Type>
	struct either<Type, Type>;

}

#endif