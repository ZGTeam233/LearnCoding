fun main() {
    val a: Int = 37
    val b: Int = 40
    println("a = " + a)
    println("b = " + b)
    val value = largerNumberIf(a, b)
    println("Larger number of a and b is " + value)
}
fun largerNumberIf(num1: Int, num2: Int): Int {
    var value: Int = 0
    if (num1 > num2) {
        value = num1
    } else {
        value = num2
    }
    return value
}
