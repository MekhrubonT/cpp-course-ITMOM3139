#include <bits/stdc++.h>

template<size_t N>
struct placeholder {};

template<>
struct placeholder<0>;

template<typename Func, typename... Args>
struct bind_t
{
	bind_t(Func &&f, Args&&... args) : 
	f(std::forward<Func>(f)), 
	t(std::forward<Args>(args)...)
	{}

	template <size_t PlN, typename... NewArgs>
	auto&& get(placeholder<PlN>, const NewArgs&... args) const {
		return std::get<PlN - 1>(std::forward_as_tuple(args...));
	}	

	template <typename El, typename... NewArgs> 
	auto&& get(const El& cur, const NewArgs&... nargs) const {
		return cur;
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
	auto call(const seq<Seq...> q, NewArgs&&... nargs) const {
		return f(get(std::get<Seq>(t), std::forward<NewArgs>(nargs)...)...);
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
auto my_bind(Func &&f, Args&&... args) {
	return bind_t<Func, Args...>(std::forward<Func>(f), std::forward<Args>(args)...);
}
