#include <iostream>

template <bool b, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

// Succ, Zero

template <typename T>
struct Succ {};

template <typename T>
struct Pred {};

struct Zero {};

// Eval

template <typename T>
struct Eval {};

template <>
struct Eval<Zero> {
  static const int value = 0;
};

template <typename T>
struct Eval<Succ<T> > {
  static const int value = 1 + Eval<T>::value;
};

template <typename T>
struct Eval<Pred<T> > {
  static const int value = Eval<T>::value - 1;
};

// Is_Less

template <typename T, typename U>
struct Is_Less {
  static const bool value = Eval<T>::value < Eval<U>::value;
};

// Add

template <typename T, typename U>
struct Add {};

template <typename T, typename U>
struct Add<T, Succ<U> > {
  typedef typename Add<Succ<T>, U>::result result;
};

template <typename T, typename U>
struct Add<T, Pred<U> > {
  typedef typename Add<Pred<T>, U>::result result;
};

template <typename T>
struct Add<T, Zero> {
  typedef T result;
};

// Sub

template <typename T, typename U>
struct Sub {};

template <typename T, typename U>
struct Sub<T, Succ<U> > {
  typedef typename Sub<Pred<T>, U>::result result;
};

template <typename T, typename U>
struct Sub<T, Pred<U> > {
  typedef typename Sub<Succ<T>, U>::result result;
};

template <typename T>
struct Sub<T, Zero> {
  typedef T result;
};

// Mul

template <typename T, typename U>
struct Mul {};

template <typename T, typename U>
struct Mul<T, Succ<U> > {
  typedef typename Add<typename Mul<T, U>::result, T>::result result;
};

template <typename T, typename U>
struct Mul<T, Pred<U> > {
  typedef typename Sub<typename Mul<T, U>::result, T>::result result;
};

template <typename T>
struct Mul<T, Zero> {
  typedef Zero result;
};

// Div FIXME: consider negative integer

template <typename T, typename U, typename = void>
struct Div {};

template <typename T, typename U>
struct Div<T, U, typename enable_if<!Is_Less<T, U>::value, void>::type> {
  typedef typename Add<Succ<Zero>, typename Div<typename Sub<T, U>::result, U>::result>::result result;
};

template <typename T, typename U>
struct Div<T, U, typename enable_if<Is_Less<T, U>::value, void>::type> {
  typedef Zero result;
};

int
main(void) {
  typedef Succ<Zero> One;
  typedef Succ<One> Two;
  typedef Succ<Two> Three;

  std::cout << Eval<Three>::value << std::endl;

  std::cout << Eval<Add<Two, Three>::result>::value << std::endl;

  std::cout << Eval<Add<Add<Two, Three>::result, Three>::result>::value
            << std::endl;

  std::cout << Eval<Mul<Two, Three>::result>::value << std::endl;

  std::cout << Eval<
      Mul<Mul<Three, Two>::result, Add<Two, Three>::result>::result>::value
            << std::endl;

  std::cout << "====" << std::endl;

  typedef Sub<Zero, One>::result MinusOne;
  typedef Pred<MinusOne> MinusTwo;
  typedef Pred<MinusTwo> MinusThree;

  std::cout << Eval<
      Sub<Add<One, Two>::result,
          Mul<MinusThree, Mul<MinusTwo, Three>::result>::result>::result>::value
            << std::endl;

  std::cout << Is_Less<Three, One>::value << std::endl;

  std::cout << Eval<
      Div<Mul<Mul<Three, Three>::result, Three>::result, Two>::result>::value
            << std::endl;

  return 0;
}
