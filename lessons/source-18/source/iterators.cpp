#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template<typename T>
struct MySuperContainer {
	struct MyIterator : std::iterator<
							std::forward_iterator_tag,  // Category
							T,												 	// T
							std::ptrdiff_t, 				 		// Distance
							T*, 							 					// Pointer
							T& 								 					// Reference
							> 
	{
		using BaseType = typename std::vector<T>::iterator;

		MyIterator(const BaseType& iter) : m_iter{iter} {

		}

		~MyIterator() = default;

		T& operator*() { return *m_iter; }
	    T& operator->() { return *m_iter; }
	    bool operator==(const MyIterator& other) const { return m_iter == other.m_iter; }
	    bool operator!=(const MyIterator& other) const { return m_iter != other.m_iter; }

	    void operator++() {
	      ++m_iter;
	    }
	private:
		BaseType m_iter;
	};

	struct MyIterator2 {

		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::forward_iterator_tag;
		// using iterator_category = std::random_access_iterator_tag;

		using BaseType = typename std::vector<T>::const_iterator;

		MyIterator2(const BaseType& iter) : m_iter{iter} {

		}

		~MyIterator2() = default;

		const T& operator*() { return *m_iter; }
	    const T& operator->() { return *m_iter; }
	    bool operator==(const MyIterator2& other) const { return m_iter == other.m_iter; }
	    bool operator!=(const MyIterator2& other) const { return m_iter != other.m_iter; }

	    void operator++() {
	      ++m_iter;
	    }
	private:
		BaseType m_iter;
	};

	MySuperContainer() = default;
	MySuperContainer(const std::initializer_list<int>& values) : m_data{values} {

	}
	~MySuperContainer() = default;

	void push_back(const T& value) {
		m_data.push_back(value);
	}

	MyIterator begin() { return MyIterator(m_data.begin()); }
  	MyIterator end()   { return MyIterator(m_data.end()); }

  	MyIterator2 begin() const { return MyIterator2(m_data.cbegin()); }
  	MyIterator2 end() const { return MyIterator2(m_data.cend()); }
private:
	std::vector<T> m_data;
};

int main() {
	MySuperContainer<int> container1;
	for (int i=0; i<10; ++i)
		container1.push_back(i);

	std::for_each(container1.begin(), container1.end(), 
		[](int v) {
			std::cout << v << ' ';
		});
	std::cout << std::endl;

	std::cout << std::distance(container1.begin(), container1.end()) << std::endl;

	for(auto& v : container1) {
		std::cout << v << ' ';
	}
	std::cout << std::endl;

	const MySuperContainer<int> container2{10, 9, 8, 7, 6, 4, 3, 2, 1, 0};
	for(const auto& v : container2) {
		std::cout << v << ' ';
	}
	std::cout << std::endl;

	std::for_each(container2.begin(), container2.end(), 
		[](int v) {
			std::cout << v << ' ';
		});
	std::cout << std::endl;

	std::cout << std::distance(container2.begin(), container2.end()) << std::endl;

	// std::cout << std::reduce(container2.begin(), container2.end(), int{}) << std::endl;

	return 0;
}