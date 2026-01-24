class Student(val sno: String = "", val grade: Int = 0, name: String = "", age: Int = 0) : Person(name, age), Study {
    init {
        println("Student number is $sno")
        println("Grade is $grade")
    }
    override fun readBooks() {
        println("$name is reading.")
    }
    override fun doHomework() {
        println("$name is doing homework.")
    }
}