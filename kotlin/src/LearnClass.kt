fun main() {
    val student1 = Student("a123", 5, "Jack", 19)
    val student2 = Student(name = "John", age = 23)
    val student3 = Student(sno = "a321", name = "Lily")
    doStudy(student1)
    student2.eat()
}
fun doStudy(study: Study) {
    study.readBooks()
    study.doHomework()
}