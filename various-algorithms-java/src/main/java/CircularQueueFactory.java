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

class CircularQueueArrayImpl<Item> implements CircularQueue<Item> {
    Item[] elements;
    int startIdx;
    int endIdx;

    public CircularQueueArrayImpl() {
        increaseSize(2);
    }
    private void increaseSize(int size) {
        Item[] newArray = (Item[]) new Object[size];
        if (elements == null) {
            elements = newArray;
            return;
        }
        if (startIdx <= endIdx) {
            for (int idx = startIdx; idx != endIdx; ++idx) {
                newArray[idx] = elements[idx];
            }
        }
        else {
            for (int idx = startIdx; idx != elements.length; ++idx) {
                newArray[idx] = elements[idx];
            }
            for (int idx = 0; idx != endIdx; ++idx) {
                newArray[idx + elements.length] = elements[idx];
            }
            endIdx += elements.length;
        }
        elements = newArray;
    }
    private void decreaseSize(int size) {
        Item[] newArray = (Item[]) new Object[size];
        if (startIdx <= endIdx) {
            for (int idx = startIdx; idx != endIdx; ++idx) {
                newArray[idx - startIdx] = elements[idx];
            }
            endIdx -= startIdx;
            startIdx = 0;
        }
        else {
            for (int idx = startIdx; idx != elements.length; ++idx) {
                newArray[idx-startIdx] = elements[idx];
            }
            for (int idx = 0; idx != endIdx; ++idx) {
                newArray[idx + elements.length -startIdx] = elements[idx];
            }
            endIdx += elements.length -startIdx;
            startIdx = 0;
        }
        elements = newArray;
    }
    public boolean empty() {
        return startIdx == endIdx;
    }
    public void enqueue(Item it) {
        if (endIdx == startIdx-1 || (startIdx == 0 && endIdx == elements.length -1)) {
            increaseSize(2 * elements.length);
        }

        elements[endIdx++] = it;
        if (endIdx == elements.length) {
            endIdx = 0;
        }
    }
    public Item dequeue() {
        Item ret = elements[startIdx];
        elements[startIdx++] = null;
        if (startIdx == elements.length) {
            startIdx = 0;
        }
        int currentSize = startIdx <= endIdx ? (endIdx-startIdx) : (elements.length-startIdx + endIdx);
        if (elements.length > 2 && 2*currentSize < elements.length) {
            decreaseSize(elements.length/2);
        }
        return ret;
    }
}

public class CircularQueueFactory {
    public static Supplier<CircularQueue<Integer>> builderCircularQueue() {
        return () -> new CircularQueueImpl<>();
    }
    public static Supplier<CircularQueue<Integer>> builderCircularQueueArray() {
        return () -> new CircularQueueArrayImpl<>();
    }
}
