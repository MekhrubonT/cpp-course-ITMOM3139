#ifndef BIND_H
#define BIND_H
#include <tuple>

namespace hw_bind {
	template<size_t N>
	struct place_holder {};

	template<>
	struct place_holder<0>;


	template<typename Func, typename... Args>
	struct bind_t
	{
		bind_t(Func &&f, Args&&... args) : 
		f(std::forward<Func>(f)), 
		t(std::forward<Args>(args)...)
		{}

		template <size_t PlN, typename... NewArgs>
		auto&& get(place_holder<PlN>, NewArgs&... args) const {
			return std::get<PlN - 1>(std::forward_as_tuple(args...));
		}	

		template <typename El, typename... NewArgs> 
		auto&& get(El&& cur, NewArgs&... nargs) const {
			return cur;
		}

		template <typename TFunc, typename... TArgs, typename... NewArgs>
		auto get(const bind_t<TFunc, TArgs...> &g, NewArgs&... nargs) const {
			return g(nargs...);
		}

		template<size_t... N> 
		struct seq {};

		template <size_t First, size_t... Seq>
		struct seq_builder
		{
			typedef typename seq_builder<First - 1, First - 1, Seq...>::type type;
		};

		template<size_t... Seq>
		struct seq_builder<0, Seq...>
		{
			typedef seq<Seq...> type;
		};

		template<size_t... Seq, typename... NewArgs>
		auto call(const seq<Seq...> &q, NewArgs&&... nargs) const {
			return f(get(std::get<Seq>(t), nargs...)...);
		}

	public:
		template <typename... NewArgs>
		auto operator()(NewArgs&&... nargs) const {
			return call(
				typename seq_builder<std::tuple_size<my_tuple>::value>::type(), 
				std::forward<NewArgs>(nargs)...
				);
		}

	private:
		typedef std::tuple<Args...> my_tuple;
		Func f;
		my_tuple t;
	};


	template<typename Func, typename... Args>
	bind_t<Func, Args...> bind(Func &&f, Args&&... args) {
		return bind_t<Func, Args...>(std::forward<Func>(f), std::forward<Args>(args)...);
	}
}
#endif