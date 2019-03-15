ary = [1, 2, 3]
ary.each { |elem|
    puts elem
}

# Compiles at its core to:
# rbxx::vector<int> ary = {1, 2, 3};
# for (int elem : ary.each())
# {
#   std::cout << elem << std::endl;
# }
# -> Optimizes to:
# std::vector<int> ary = {1, 2, 3};
# for (int elem : ary)
# {
#   std::cout << elem << std::endl;
# }
# This reduces the amount of function calls
# And allocation of classes as it doesn't make
# Use of a Enumerator class/system

ary = [3, 2, 1]
ary.reverse_each { |elem|
    puts elem
}

# Compiles at its core to:
# rbxx::vector<int> ary = {3, 2, 1};
# for (int elem : ary.reverse().each())
# {
#   std::cout << elem << std::endl;
# }
# -> Optimizes to:
# std::vector<int> ary = {3, 2, 1};
# for (auto it = v.rbegin(); it != v.rend(); ++it)
# {
#   int elem = *it;
#   std::cout << elem << std::endl;
# }
# Half as many function calls
# No copy construction
# And a no enumerator is generated.
