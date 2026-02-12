package com.github.zgteam233.kotlin.lambda

import java.util.Locale.getDefault

fun main() {
    val list = listOf("Apple", "Banana", "Orange", "Pear", "Grape", "Watermelon")
    println("list")
    for (fruit in list) {
        print("$fruit ")
    }
    println("\n")
    val set = setOf("Apple", "Banana", "Orange", "Pear", "Grape")
    println("set")
    for (fruit in set) {
        print("$fruit ")
    }
    println("\n")
    val map = mapOf("Apple" to 1, "Banana" to 2, "Orange" to 3, "Pear" to 4, "Grape" to 5)
    println("map")
    for ((fruit, number) in map) {
        println("水果为 $fruit，编号为 $number")
    }
    println("")

    val maxLengthFruit = list.maxBy { it.length }
    println("list 中单词最长的水果为 $maxLengthFruit")
    println("")

    val newList = list.filter { it.length <= 5 }
        .map { it.uppercase(getDefault()) }
    println("将 list 单词长度小于等于五的水果过滤出来后大写")
    for (fruit in newList) {
        print("$fruit ")
    }
    println("")

    val anyResult = list.any { it.length <= 5 }
    val allResult = list.all { it.length <= 5 }
    println("anyResult 是 $anyResult，allResult 是 $allResult")
}