template <typename T>
class Test {
 private:
  T data;

 public:
  Test(const T& e = 0) { data = e; }
  T& data() { return data; }
};
int main() {
  int a = int();

  return 0;
}