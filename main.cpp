#include <iostream>
#include <memory>

class A
{
public:
    template <typename... Args>
    static std::shared_ptr<A> create(Args &&... args);

private:
    explicit A() {std::cout << "no param ctor called\n";}
    explicit A(int i) {std::cout << "int ctor called\n";}
    
    struct A_shared_enabler;
};

struct A::A_shared_enabler : public A
{
    template <typename... Args>
    A_shared_enabler(Args &&... args)
    :A(std::forward<Args>(args)...)
    {
    }
};

template <typename... Args>
std::shared_ptr<A> A::create(Args &&... args)
{
    return std::make_shared<A_shared_enabler>(args...);
}

int main() {
    auto ptr1 = A::create();
    auto ptr2 = A::create(1);
    // auto ptr3 = A::create(1, 2);  // compilation error: no A::A(int, int)
}
