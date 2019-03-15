
puts "--------------------"
puts "VecInt time!"
vint = VecInt.new()
puts "vint.empty?=#{vint.empty?}"
vint.push(10)
vint.push(20)
vint << 30
puts "vint[0]=#{vint[0]}"
puts "vint[1]=#{vint[1]}"
puts "vint[2]=#{vint[2]}"
puts "vint.empty?=#{vint.empty?}"

vint[1] = 25
vint.insert(1, 15)
vint.insert(1, 55)

vint.each { |iter|
    puts "iter: #{iter}"
}

puts "------------------------------------"

puts "vint.sort.each { |iter| block }"
vint.sort.each { |iter|
    puts "Sorted iter: #{iter}"
}

puts "------------------------------------"

puts "vint.each_index { |i| block }"
vint.each_index { |i|
    puts "i: #{i}"
}

puts "------------------------------------"

puts "vint.pop()=#{vint.pop()}"
vint << 35

puts "------------------------------------"

puts "vint.reverse_each { |riter| block }"
vint.reverse_each { |riter|
    puts "riter: #{riter}"
}

puts "------------------------------------"
puts "vint.reverse.each { |riter| block }"
vint.reverse.each { |riter| 
    puts "riter: #{riter}"
}

puts "------------------------------------"
puts "vint.max()=#{vint.max()}"
puts "vint.min()=#{vint.min()}"
puts "vint.first()=#{vint.first()}"
puts "vint.last()=#{vint.last()}"

puts "------------------------------------"
puts "vint.shuffle.each { |shuffle_iter| block }"
vint.shuffle.each { |shuffle_iter| 
    puts "shuffle_iter: #{shuffle_iter}"
}

vint << 35
puts "------------------------------------"
puts "vint.uniq.each { |uiter| block }"
vint.uniq.each { |uiter| 
    puts "uiter: #{uiter}"
}

puts "------------------------------------"
puts "vint.uniq!"
puts "vint.each { |uiter| block }"
vint.uniq!
vint.each { |uiter| 
    puts "uiter: #{uiter}"
}
puts "------------------------------------"
puts "vint.index(10)=#{vint.index(10)}"
puts "vint.index(55)=#{vint.index(55)}"
puts "vint.index(15)=#{vint.index(15)}"
puts "vint.index(25)=#{vint.index(25)}"
puts "vint.index(35)=#{vint.index(35)}"
puts "------------------------------------"
puts "vint.rindex(10)=#{vint.rindex(10)}"
puts "vint.rindex(55)=#{vint.rindex(55)}"
puts "vint.rindex(15)=#{vint.rindex(15)}"
puts "vint.rindex(25)=#{vint.rindex(25)}"
puts "vint.rindex(35)=#{vint.rindex(35)}"