import kotlin.math.max

fun main() {
    val a: Int = 37
    val b: Int = 40
    println("a = " + a)
    println("b = " + b)
    val value = largerNumber(a, b)
    println("Larger number of a and b is " + value)
}
private fun largerNumber(num1: Int, num2: Int): Int {
    return max(num1, num2)
}
