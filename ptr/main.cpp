#include <iostream>
#include <vector>
#include <memory>

class tridiagonal_matrix
{
public:
    std::vector<double> m_down;
    std::vector<double> m_upper;
    std::vector<double> m_middle;

    tridiagonal_matrix(
        const std::vector<double>& down,
        const std::vector<double>& upper,
        const std::vector<double>& middle) :
        m_down{ down }, m_upper{ upper }, m_middle{ middle }
    {};

    ~tridiagonal_matrix() { 
        std::cout << "destructor matrix called\n"; 
    }

    // clone
    std::unique_ptr<tridiagonal_matrix> clone() const {
        return std::make_unique<tridiagonal_matrix>(m_down, m_upper, m_middle);
    }
};


class node
{
public:
    int m_value;
    std::weak_ptr<node> parent; // weak_ptr
    node(int value) : m_value{ value } {};
    ~node() { std::cout << "destructor called\n"; }
};

int main()
{
    auto down = std::vector<double>{ -4.0, 5.0 };
    auto upper = std::vector<double>{ 14.0, 8.0 };
    auto middle = std::vector<double>{ 3.0, 1.0, 7.0 };
    auto matrix = std::make_unique<tridiagonal_matrix>(
        down,
        upper,
        middle
    );

    auto matrix_clone = matrix->clone();

    // Проверка правильности копирования
    std::cout << "Original matrix:\n";
    std::cout << "Upper: ";
    for (const auto& val : matrix->m_upper) std::cout << val << " ";
    std::cout << "\nMiddle: ";
    for (const auto& val : matrix->m_middle) std::cout << val << " ";
    std::cout << "\nDown: ";
    for (const auto& val : matrix->m_down) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Cloned matrix:\n";
    std::cout << "Upper: ";
    for (const auto& val : matrix_clone->m_upper) std::cout << val << " ";
    std::cout << "\nMiddle: ";
    for (const auto& val : matrix_clone->m_middle) std::cout << val << " ";
    std::cout << "\nDown: ";
    for (const auto& val : matrix_clone->m_down) std::cout << val << " ";
    std::cout << "\n";


    {
        auto node1 = std::make_shared<node>(1);
        auto node2 = std::make_shared<node>(2);
        std::cout << "\n";
        node1->parent = node2; // node1 хранит weak_ptr на node2
        node2->parent = node1; // node2 хранит weak_ptr на node1
    }
    return 0;
}