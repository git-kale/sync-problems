# Solutions to the most common problems in synchronization and concurrency

### <u>1) Dining Philospher's Problem</u>
    
<div style="padding:20px">The Dining Philosopher Problem states that K philosophers seated around a circular table with one chopstick between each pair of philosophers. There is one chopstick between each philosopher. A philosopher may eat if he can pickup the two chopsticks adjacent to him. One chopstick may be picked up by any one of its adjacent followers but not both.</div>

### <u>2) Ciggarate Smokers' Problem</u>
    
<div style="padding:20px">Assume a cigarette requires three ingredients to make and smoke: tobacco, paper, and matches. There are three smokers around a table, each of whom has an infinite supply of one of the three ingredients — one smoker has an infinite supply of tobacco, another has paper, and the third has matches.

There is also a non-smoking agent who enables the smokers to make their cigarettes by arbitrarily (non-deterministically) selecting two of the supplies to place on the table. The smoker who has the third supply should remove the two items from the table, using them (along with their own supply) to make a cigarette, which they smoke for a while. Once the smoker has finished his cigarette, the agent places two new random items on the table. This process continues forever.</div>

### <u>3) Producer Consumer Problem</u>
    
<div style="padding:20px">The problem describes two processes, the producer and the consumer, who share a common, fixed-size buffer used as a queue. The producer's job is to generate data, put it into the buffer, and start again. At the same time, the consumer is consuming the data (i.e., removing it from the buffer), one piece at a time. The problem is to make sure that the producer won't try to add data into the buffer if it's full and that the consumer won't try to remove data from an empty buffer.</div>

### <u>4) Sleeping Barber Problem</u>

<div style="padding:20px">The barber has one barber's chair in a cutting room and a waiting room containing a number of chairs in it. When the barber finishes cutting a customer's hair, he dismisses the customer and goes to the waiting room to see if there are others waiting. If there are, he brings one of them back to the chair and cuts their hair. If there are none, he returns to the chair and sleeps in it.

Each customer, when they arrive, looks to see what the barber is doing. If the barber is sleeping, the customer wakes him up and sits in the cutting room chair. If the barber is cutting hair, the customer stays in the waiting room. If there is a free chair in the waiting room, the customer sits in it and waits their turn. If there is no free chair, the customer leaves. </div>

### 5) <u>Reader Writer Problem</u>

<div style="padding:20px">Consider a situation where we have a file shared between many people.

--> If one of the people tries editing the file, no other person should be reading or writing at the same time, otherwise changes will not be visible to him/her.

---> However if some person is reading the file, then others may read it at the same time.</div>


## How to compile

The implementations use pthread library so a pthread flag must be set during compilation.
    
    make solution

## How to remove binary

    make clean
