import java.util.function.Supplier;

/**
 * Created by Nicolas DUBIEN on 04/03/2017.
 *
 * Queue implementation that uses a circular linked-list
 *
 * constraints:
 * - no links are null
 * - last.next = first
 *
 * assumptions:
 * - no need to check for size on dequeue
 *
 * Taken from Algorithms Fourth Edition
 * from Robert Sedgewick and Kevin Wayne
 */

interface CircularQueue<Item> {
    void enqueue(Item it);
    Item dequeue();
    boolean empty();
}

class CircularQueueImpl<Item> implements CircularQueue<Item> {
    private class Node {
        Item it;
        Node next;
    }

    Node first;
    Node last;

    public CircularQueueImpl() {}
    public boolean empty() {
        return first == null;
    }
    public void enqueue(Item it) {
        Node n = new Node();
        n.it = it;
        if (first == null) {
            first = n;
            last = n;
            n.next = n;
        }
        else {
            n.next = first;
            last.next = n;
            last = n;
        }
    }
    public Item dequeue() {
        Item top = first.it;
        if (first == last) {
            first = null;
            last = null;
        }
        else {
            last.next = first.next;
            first = first.next;
        }
        return top;
    }
}

public class CircularQueueFactory {
    public static Supplier<CircularQueue<Integer>> builderCircularQueue() {
        return () -> new CircularQueueImpl<>();
    }
}
