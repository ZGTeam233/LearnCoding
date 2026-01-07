import kotlin.math.max

fun main() {
    val a: Int = 37
    val b: Int = 40
    println("a = " + a)
    println("b = " + b)
    val value = largerNumberA(a, b)
    println("Larger number of a and b is " + value)
}
fun largerNumberA(num1: Int, num2: Int): Int {
    return max(num1, num2)
}
