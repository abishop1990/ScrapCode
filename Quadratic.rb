=begin

Quadratic Formula in Ruby

My bro wanted some math help so...why not?

Written by Alan Bishop 7/10/14

=end

print "Enter a: "
a = gets.chomp.to_f
print "Enter b: "
b = gets.chomp.to_f
print "Enter c: "
c = gets.chomp.to_f


#First off some basic bounds checking...
if a == 0
    puts "Error: Division by 0! (a == 0)"
    exit
end

radValue = b*b - 4*a*c

if radValue < 0
    puts "Error: No real solutions"
    exit
end


denom = 2*a
bneg = -1 * b
radical = Math.sqrt(radValue)
num1 = bneg + radical
num2 = bneg - radical

sol1 = (num1)/denom
sol2 = (num2)/denom

puts "Real value solutions: #{sol1}, #{sol2}"
puts "Fraction values: #{num1}/#{denom}, #{num2}/#{denom}"
puts "Unreduced values: ( #{bneg} +/- sqrt(#{radValue}) ) / #{denom}"
    
