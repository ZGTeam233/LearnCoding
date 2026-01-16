fun main() {
    println("Hello World!")
    val a: Int = 37
    val b: Int = 40
    println("a = " + a)
    println("b = " + b)
    val value = largerNumber(a, b)
    println("Larger number of a and b is " + value)
    val n = "Tom"
    println(n + "'s score is " + getScore(n))
}
fun largerNumber(num1: Int, num2: Int) = if (num1 > num2) num1 else num2
fun getScore(name: String) = when (name) {
    "Tom" -> 86
    "Jim" -> 77
    "Jack" -> 95
    "Lily" -> 100
    else -> 0
}
