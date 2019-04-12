# puts "exist?: #{RbxxFile.exist?("does_exist")}"
# puts "exists?: #{RbxxFile.exists?("does_exist")}"
puts "#{RbxxFile.expand_path("tests/file/../argparse")}"
# File.expand_path("tests/file/../argparse") == 
RbxxFile.expand_path("tests/file/../argparse")