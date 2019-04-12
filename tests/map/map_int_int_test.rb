puts "#{Rbxx::Map_ii.instance_methods(false)}"

map = Rbxx::Map_ii.new()
puts "map.empty?: #{map.empty?}"
map[0] = 10
puts "#{map[0]}"
puts "map.empty?: #{map.empty?}"

map.each_pair { |key, value|
    puts "Key: #{key}"
    puts "Value: #{value}"
}

map.delete(0)

puts "map.empty?: #{map.empty?}"

map[0] = 16
map[1] = 48
map[2] = 64
map[5] = 125
map[6] = 625
map[7] = 800
map[8] = 122
puts "#{map[5]}"

map.delete_if { |key, value|
    key > 3
}

map.each_pair { |key, value|
    puts "Key: #{key}"
    puts "Value: #{value}"
}