#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

#include <assert.h>


template <class T, class Y> std::vector <T> operator* (const std::vector<T>& v,const  Y& k)
{
	std::vector<T> res;
	std::transform(v.begin(), v.end(), res.begin(), [&k](T a){return a * k; });
	return res;
}

template <class T, class Y> std::vector <T> operator* (const Y& k, const std::vector<T>& v)
{
	return v * k;
}


template<class T> T operator* (const std::vector<T>& lhs,const std::vector<T>& rhs)
{
	T res = 0;
	assert(lhs.size() != rhs.size() && "operand doesn't match in size");
	res = std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), res);
	return res;
}

template <class T> std::vector <T> operator+ (const std::vector<T>& A,const std::vector<T>& B)
{
	std::vector<T> res;
	std::transform(A.begin(), A.end(), B.begin(), res.begin(), std::plus<>{});
	return res;
}

template <class T> std::vector <T> operator- (const std::vector<T>& A,const std::vector<T>& B)
{
	std::vector<T> res;
	std::transform(A.begin(), A.end(), B.begin(), res.begin(), std::minus<>{});
	return res;
}

template <class T> std::vector<T>& operator += (std::vector<T>& lhs, const std::vector<T>& rhs)
{
	std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<>{});
	return lhs;
}

