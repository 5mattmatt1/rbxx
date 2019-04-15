require './map'
puts "---------------------------------------"
# puts "#{Rbxx::Map_ii.instance_methods(false)}"
# puts "#{Hash.instance_methods(false)}"
puts "---------------------------------------"
puts "Number of Map methods:  #{Rbxx::Map_ii.instance_methods(false).size}"
puts "Number of Hash methods: #{Hash.instance_methods(false).size}"
unimplemented_methods = Hash.instance_methods(false).select { |method|
    !Rbxx::Map_ii.instance_methods(false).include?(method)
}
puts "Unimplemented methods: #{unimplemented_methods.sort}"
puts "---------------------------------------"

optional = Rbxx::Map_ii.new()
optional[nil] = 5
puts "optional[nil] = #{optional[nil]}"
puts "optional.compact[nil] = #{optional.compact[nil]}"

# map = Rbxx::Map_ii.new()
# puts "map.empty?: #{map.empty?}"
# map[0] = 10
# puts "#{map[0]}"
# puts "map.empty?: #{map.empty?}"

# map.each_pair { |key, value|
#     puts "Key: #{key}"
#     puts "Value: #{value}"
# }

# map.delete(0)

# puts "map.empty?: #{map.empty?}"

# map[0] = 16
# map[1] = 48
# map[2] = 64
# map[5] = 125
# map[6] = 625
# map[7] = 800
# map[8] = 122
# puts "#{map[5]}"



# puts "---------------------------------------"
# map.delete_if { |key, value|
#     key > 3
# }

# puts "Deleted: key > 3"
# map.each_pair { |key, value|
#     puts "Key: #{key}, Value: #{value}"
# }

# puts "---------------------------------------"
# puts "Inverted:"
# inverted = map.invert
# inverted.each_pair { |key, value|
#     puts "Key: #{key}, Value: #{value}"
# }

# puts "---------------------------------------"
# puts "Kept: value < 2"
# inverted.keep_if { |key, value|
#     value < 2
# }

# inverted.each_pair { |key, value|
#     puts "Key: #{key}, Value: #{value}"
# }

# puts "---------------------------------------"
# # key that maps to value of 1
# key = inverted.key(1)
# puts "inveted.key(1) = #{inverted.key(1)}"
# puts "inverted.has_key?(key) = #{inverted.key?(key)}"

# puts "---------------------------------------"
# puts "Updating with: {96 => 3, 128 => 4, 160 => 5}"
# src = Rbxx::Map_ii.new()
# src[96] = 3
# src[128] = 4
# src[160] = 5

# inverted.update(src) # {|key, v1, v2| v2}
# inverted.each_pair { |key, value|
#     puts "Key: #{key}, Value: #{value}"
# }

# puts "---------------------------------------"
# puts "Transformed:"
# transformed = inverted.transform_keys { |key, value|
#     (key / 32)
# }

# inverted.transform_keys! { |key, value|
#     (key / 32)
# }

# inverted.transform_keys! { |key, value|
#     (key * 32)
# }

# transformed.each_pair { |key, value|
#     puts "Key: #{key}, Value: #{value}"
# }


# puts "--------------------------------------"
# puts "Default_proc testing"
# proc_test = Rbxx::Map_ii.new
# puts "proc_test[2] = #{proc_test[2]}"
# proc_test.default = 5
# proc_test.default_proc = Proc.new { |hsh, key|
#     key + key
# }

# puts "proc_test[2] = #{proc_test[2]}"

# puts "--------------------------------------"
# puts "Conversion:"
# conv_test = Rbxx::Map_ii.new
# conv_test[0] = 1
# conv_test[1] = 2
# conv_test[2] = 4
# conv_test[3] = 8
# puts "conv_test.to_h=#{conv_test.to_h}"
# puts "conv_test.to_h.class=#{conv_test.to_h.class}"
# puts "conv_test.to_hash=#{conv_test.to_hash}"
# puts "conv_test.to_hash.class=#{conv_test.to_hash.class}"

# puts "|####################################|"
# puts "|************************************|"
# puts "|####################################|"
# puts "Comparators: "
# cmp_foo = Rbxx::Map_ii.new
# cmp_foo[0] = 1
# cmp_foo[2] = 4
# cmp_foo[1] = 2

# cmp_bar = Rbxx::Map_ii.new
# cmp_bar[0] = 1
# cmp_bar[1] = 2
# cmp_bar[2] = 4
# cmp_bar[3] = 8

# puts "cmp_foo is subset of cmp_bar: (lt) #{cmp_foo < cmp_bar}"
# puts "cmp_bar is subset of cmp_foo: (lt) #{cmp_bar < cmp_foo}"
# puts "cmp_foo is subset of cmp_foo: (lt) #{cmp_foo < cmp_foo}"
# puts "cmp_bar is subset of cmp_bar: (lt) #{cmp_bar < cmp_bar}"
# puts "--------------------------------------"
# puts "cmp_foo is subset of cmp_bar: (gt) #{cmp_bar > cmp_foo}"
# puts "cmp_bar is subset of cmp_foo: (gt) #{cmp_foo > cmp_bar}"
# puts "cmp_foo is subset of cmp_foo: (gt) #{cmp_foo > cmp_foo}"
# puts "cmp_bar is subset of cmp_bar: (gt) #{cmp_bar > cmp_bar}"
# puts "--------------------------------------"
# puts "cmp_foo is equal to cmp_foo: (eql) #{cmp_foo == cmp_foo}"
# puts "cmp_bar is equal to cmp_bar: (eql) #{cmp_bar == cmp_bar}"
# puts "--------------------------------------"
# puts "cmp_foo is subset of or equal to cmp_bar: (lte) #{cmp_foo <= cmp_bar}"
# puts "cmp_bar is subset of or equal to cmp_foo: (lte) #{cmp_bar <= cmp_foo}"
# puts "cmp_foo is subset of or equal to cmp_foo: (lte) #{cmp_foo <= cmp_foo}"
# puts "cmp_bar is subset of or equal to cmp_bar: (lte) #{cmp_bar <= cmp_bar}"
# puts "--------------------------------------"
# puts "cmp_foo is subset of or equal to cmp_bar: (gte) #{cmp_bar >= cmp_foo}"
# puts "cmp_bar is subset of or equal to cmp_foo: (gte) #{cmp_foo >= cmp_bar}"
# puts "cmp_foo is subset of or equal to cmp_foo: (gte) #{cmp_foo >= cmp_foo}"
# puts "cmp_bar is subset of or equal to cmp_bar: (gte) #{cmp_bar >= cmp_bar}"
