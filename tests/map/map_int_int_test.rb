require './map'
puts "---------------------------------------"
puts "#{Rbxx::Map_ii.instance_methods(false)}"
puts "#{Hash.instance_methods(false)}"
puts "---------------------------------------"
puts "Number of Map methods:  #{Rbxx::Map_ii.instance_methods(false).size}"
puts "Number of Hash methods: #{Hash.instance_methods(false).size}"
puts "---------------------------------------"

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



puts "---------------------------------------"
map.delete_if { |key, value|
    key > 3
}

puts "Deleted: key > 3"
map.each_pair { |key, value|
    puts "Key: #{key}, Value: #{value}"
}

puts "---------------------------------------"
puts "Inverted:"
inverted = map.invert
inverted.each_pair { |key, value|
    puts "Key: #{key}, Value: #{value}"
}

puts "---------------------------------------"
puts "Kept: value < 2"
inverted.keep_if { |key, value|
    value < 2
}

inverted.each_pair { |key, value|
    puts "Key: #{key}, Value: #{value}"
}

puts "---------------------------------------"
# key that maps to value of 1
key = inverted.key(1)
puts "inveted.key(1) = #{inverted.key(1)}"
puts "inverted.has_key?(key) = #{inverted.key?(key)}"

puts "---------------------------------------"
puts "Updating with: {96 => 3, 128 => 4, 160 => 5}"
src = Rbxx::Map_ii.new()
src[96] = 3
src[128] = 4
src[160] = 5

inverted.update(src) # {|key, v1, v2| v2}
inverted.each_pair { |key, value|
    puts "Key: #{key}, Value: #{value}"
}

puts "---------------------------------------"
puts "Transformed:"
transformed = inverted.transform_keys { |key, value|
    (key / 32)
}

inverted.transform_keys! { |key, value|
    (key / 32)
}

inverted.transform_keys! { |key, value|
    (key * 32)
}

transformed.each_pair { |key, value|
    puts "Key: #{key}, Value: #{value}"
}


