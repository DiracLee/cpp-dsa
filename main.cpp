template <typename T>
class Test {
 private:
  T data;

 public:
  Test(const T& e = 0) { data = e; }
  T& data { return data; }
};
int main() {
  Test<int> t = Test<int>(11);
  int a = 4;
  t.data = a;
  return 0;
}