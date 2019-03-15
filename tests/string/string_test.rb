str = RbxxString.new("Hello World!")
puts str

puts RbxxString.new("Hello ") + RbxxString.new("Mars!")
puts RbxxString.new("Hello ") + "Ruby!"
puts "Hello " + RbxxString.new("C++!")

puts "------------------------------------"

rb_str = "Quack"
rb_str << RbxxString.new("y duck!")
puts "rb_str=#{rb_str}"

rbxx_str = RbxxString.new("Quack")
rbxx_str << "y duck!"
puts "rbxx_str=#{rbxx_str}"

puts "------------------------------------"
rbxx_str1 = RbxxString.new("Hello World!")
rbxx_str2 = RbxxString.new("Hello World!")

rb_str1 = "Hello World!"
rb_str2 = "Hello World!"

puts "rbxx_str1<=>rbxx_str2 = #{rbxx_str1 <=> rbxx_str2}"
puts "rb_str1<=>rb_str2 = #{rb_str1 <=> rb_str2}"
puts "rbxx_str1<=>rb_str2 = #{rbxx_str1 <=> rb_str2}"
puts "rb_str1<=>rbxx_str2 = #{rb_str1 <=> rbxx_str2}"
puts "------------------------------------"
puts "rbxx_str1==rbxx_str2 = #{rbxx_str1 == rbxx_str2}"
puts "rb_str1==rb_str2 = #{rb_str1 == rb_str2}"
puts "rbxx_str1==rb_str2 = #{rbxx_str1 == rb_str2}"
puts "rb_str1==rbxx_str2 = #{rb_str1 == rbxx_str2}"