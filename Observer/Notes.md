# Observer Design Pattern

<details>
<summary>What are fundamental building blocks of Observer Design Pattern?</summary>
The Observer pattern consists of two elements:</br></br>
1. <b>Subject</b>: That is the subject of observation and is the porducer of new information that is consumed by `Observer`</br>
2. <b>Observer</b>: The one that observes the `subject` and is subscriber to the changes in state of the subject or consumer of the information produced by the `subject`.</br>
The Observer model can also be called <b>Publisher - Subscriber</b> pattern.
</details>

<details>
<summary>What are basic facilities provided by the `Subject` or `Producer`?</summary>
- The `Subject` must have a way of letting `Observers` subscribe and unsubscribe for the state change or new information.
</details>

<details>
<summary>Define Observer Design Pattern</summary>
Def'n: Observer Pattern defines an one-to-many relation between objects such that the change in the state of the Subject is notified to the dependent objects automatically.
</details>

### Class Diagram
```mermaid
classDiagram
SubjectInterface <|.. ConcreteSubject : Implements
SubjectInterface : register(ObserverInterface* observer) int uid
SubjectInterface : remove(int uid)
SubjectInterface : notify()
SubjectInterface : ObserverInterface[] observers

ObserverInterface <|.. ConcreteObserver : Implements
ObserverInterface : update(void* data)

ConcreteSubject "1" *-- "*" ConcreteObserver: contains  
```