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

puts "------------------------------------"
puts "rb_str1[0]=#{rb_str1[0]}"
puts "rbxx_str1[0]=#{rbxx_str1[0]}"
puts "(rb_str1[12]==nil)=#{rb_str1[12] == nil}"
puts "(rbxx_str1[12]==nil)=#{rbxx_str1[12] == nil}"

puts "------------------------------------"
begin
    rb_str1[13] = 'Ba'
rescue IndexError
    puts "IndexError rescued!"
end

begin
    rbxx_str1[13] = 'Ba'
rescue IndexError
    puts "IndexError rescued!"
end

puts "------------------------------------"
# Current RbxxString will not raise an exception
# if index is greater than string length.
rb_str1[0] = 'Ba'
rbxx_str1[0] = 'Ba'
puts rb_str1
puts rbxx_str1

rb_str1 = 'Hello World!'
rbxx_str1 = RbxxString.new('Hello World!')
puts "------------------------------------"
puts "rb_str1.upcase=#{rb_str1.upcase}"
puts "rbxx_str1.upcase=#{rbxx_str1.upcase}"

puts "------------------------------------"

puts "rb_str1.upcase!=#{rb_str1.upcase!}"
puts "rb_str1.upcase!=#{rbxx_str1.upcase!}"
puts "rb_str1=#{rb_str1}"
puts "rbxx_str1=#{rbxx_str1}"

rb_str1 = 'Hello World!'
rbxx_str1 = RbxxString.new('Hello World!')
puts "------------------------------------"

puts "rb_str1.downcase=#{rb_str1.downcase}"
puts "rbxx_str1.downcase=#{rbxx_str1.downcase}"

puts "------------------------------------"

puts "rb_str1.downcase!=#{rb_str1.downcase!}"
puts "rb_str1.downcase!=#{rbxx_str1.downcase!}"
puts "rb_str1=#{rb_str1}"
puts "rbxx_str1=#{rbxx_str1}"

rb_str1 = 'Hello World!'
rbxx_str1 = RbxxString.new('Hello World!')
puts "------------------------------------"

puts "rb_str1.swapcase=#{rb_str1.swapcase}"
puts "rbxx_str1.swapcase=#{rbxx_str1.swapcase}"

puts "------------------------------------"

puts "rb_str1.swapcase!=#{rb_str1.swapcase!}"
puts "rbxx_str1.swapcase!=#{rbxx_str1.swapcase!}"
puts "rb_str1=#{rb_str1}"
puts "rbxx_str1=#{rbxx_str1}"

rb_str1 = 'Hello World!'
rbxx_str1 = RbxxString.new('Hello World!')
puts "------------------------------------"
# rb_str1.each_char { |chr|
#     puts chr
# }

# rbxx_str1.each_char { |chr|
#     puts chr
# }