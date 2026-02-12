package com.github.zgteam233.kotlin.lambda

fun main() {
    val list = mutableListOf("Apple", "Banana", "Orange", "Pear", "Grape")
    list.add("Watermelon")
    for (fruit in list) {
        print("$fruit ")
    }
    println()
    val set = setOf("Apple", "Banana", "Orange", "Pear", "Grape")
    for (fruit in set) {
        print("$fruit ")
    }
    println()
    val map = mapOf("Apple" to 1, "Banana" to 2, "Orange" to 3, "Pear" to 4, "Grape" to 5)
    for ((fruit, number) in map) {
        println("水果为 $fruit，编号为 $number")
    }
}