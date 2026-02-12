package com.github.zgteam233.kotlin.classnull

import java.util.Locale.getDefault

var content: String? = null

fun main() {
    val student1 = Student("a123", 5, "Jack", 19)
    val student2 = Student(name = "John", age = 23)
    doStudy(student1)
    student2.eat()
    println()

    val a = null
    val b = "Hello World!"
    val c = a ?: b
    println("c 为 “$c”")
    println("c 的长度为 ${getTextLength(c)}")

    if (content != null) {
        println()
        printUpperCase()
    }
}

fun doStudy(study: Study?) {
    study?.let {
        it.readBooks()
        it.doHomework()
    }
}

fun getTextLength(text: String?): Int = text?.length ?: 0

fun printUpperCase() {
    val upperCase = content!!.uppercase(getDefault())
    println(upperCase)
}