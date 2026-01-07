import kotlin.math.max

fun main() {
    val a: Int = 37
    val b: Int = 40
    println("a = " + a)
    println("b = " + b)
    val value = largerNumberB(a, b)
    println("Larger number of a and b is " + value)
}
fun largerNumberB(num1: Int, num2: Int) = max(num1, num2)

