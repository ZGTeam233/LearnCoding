package com.github.zgteam233.kotlin.learnkotlin

fun main() {
    println("Hello World!")
    println("你好，世界！ ")
    println("")

    val a: Int = 37
    val b: Int = 40
    println("a = " + a)
    println("b = " + b)
    val value = largerNumber(a, b)
    println("a 和 b 中最大值为 $value")
    println("")

    val n = "Tom"
    println("$n 的分数为 ${getScore(n)}")
    println("")

    var range = 0..10
    for (i in range) {
        print("$i ")
    }
    println()
    range = 0 until 10
    for (i in range) {
        print("$i ")
    }
    println()
    for (i in range step 2) {
        print("$i ")
    }
    println()
    for (i in 10 downTo 0) {
        print("$i ")
    }
}

fun largerNumber(num1: Int, num2: Int) = if (num1 > num2) num1 else num2

fun getScore(name: String) = when (name) {
    "Tom" -> 86
    "Jim" -> 77
    "Jack" -> 95
    "Lily" -> 100
    else -> 0
}
