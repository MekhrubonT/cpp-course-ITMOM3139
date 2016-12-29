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
			std::cout << "either(Left const& arg)\n";
			// reinterpret_cast<Right*>(&data);
			new (&data) Left(arg);
			std::cout << "Left=" << arg << "\n";
		}
		either(Right arg) : type(RIGHT) {
			std::cout << "either(Right const& arg)\n";
			new (&data) Right(std::move(arg));
		}

		either(either const& other) : type(get_base(other.type)) {
			std::cout << "either(either const& arg)\n";
			if (other.is_left()) {
				// reinterpret_cast<Left*>(&data);
				new (&data) Left(other.left());
			} else {
				// reinterpret_cast<Right*>(&data);
				new (&data) Right(other.right());
			}
		}
		either(either&& other) : type(get_base(other.type)) {
			std::cout << "either(either&& arg)\n";
			if (other.is_left()) {
				// reinterpret_cast<Left*>(&data);
				new (&data) Left(other.left());
			} else {
				// reinterpret_cast<Right*>(&data);
				new (&data) Right(other.right());
			}
		}

		void clear_data() {
			if (is_left()) {
				reinterpret_cast<Left*>(&data)->~Left();
			} else {
				reinterpret_cast<Right*>(&data)->~Right();
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

		template<typename Type, typename... Args>
		void emplace(Args&&... args) {
			clear_data();
			new (&data) Type(args...);
		}	

		template<typename NType, typename Type, typename... Args>
		void emplaceHeap (Type old, type_t newType, Args&&... args) {
			auto tmp = std::make_unique<Type>(old);
			try {
				clear_data();
				new (&data) NType(args...);					
				type = newType;
			} catch (std::exception e) {
				type = heap(newType);
				new (&data) std::unique_ptr<Type>(tmp.release());
			}	
		}

		template<typename... Args>
		void emplace(emplace_left_t, Args&&... args) {
			if (std::is_nothrow_constructible<Left, Args...>::value) {
				emplace<Left>(args...);
			} else if (type == LEFT) {
				emplaceHeap<Left>(left(), LEFT, args...);
			} else {
				emplaceHeap<Left>(right(), LEFT, args...);				
			}
		}
		
		template<typename... Args>
		either(emplace_left_t, Args&&... args) : type(LEFT) {
			new (&data) Left(args...);
		}


		template<typename... Args>
		void emplace(emplace_right_t, Args&&... args) {
			if (std::is_nothrow_constructible<Right, Args...>::value || is_heap(type)) {
				emplace<Right>(args...);
			} else if (type == LEFT) {
				emplaceHeap<Right>(left(), RIGHT, args...);
			} else {
				emplaceHeap<Right>(right(), RIGHT, args...);				
			}
		}

		template<typename... Args>
		either(emplace_right_t, Args&&... args) : type(RIGHT) {
			new (&data) Right(args...);
		} 

private:
		typedef typename std::aligned_storage<std::max({sizeof(std::unique_ptr<Left>), sizeof(Left), sizeof(Right)}), 
								std::max({alignof(std::unique_ptr<Left>), alignof(Left), alignof(Right)})>::type
								data_t;
		type_t type;
		data_t data;	
	};

	template<typename F, typename Left, typename Right>
	auto apply(F const& f, either<Left, Right> const& cur) {
		if (cur.is_left()) {
			f(cur.left());
		} else {
			f(cur.right());
		}
	}

	template<typename F, typename Left, typename Right>
	auto apply(F const& f, either<Left, Right>& cur) {
		if (cur.is_left()) {
			f(cur.left());
		} else {
			f(cur.right());
		}
	}

	template<typename Left, typename Right>	
	void swap(either<Left, Right> &lhs, either<Left, Right> &rhs); // Strong Exception Safety

	template<typename Type>
	struct either<Type, Type>;

}

#endif