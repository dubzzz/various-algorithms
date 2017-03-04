import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Collection;
import java.util.Queue;
import java.util.function.Supplier;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * Created by Nicolas DUBIEN on 04/03/2017.
 */
@RunWith(Parameterized.class)
public class CircularQueueFactoryTest {
    private final String implementationName;
    private final Supplier<CircularQueue<Integer>> builder;
    public CircularQueueFactoryTest(final String implementationName, final Supplier<CircularQueue<Integer>> builder) {
        this.implementationName = implementationName;
        this.builder = builder;
    }

    @Test
    public void emptyQueueIsEmpty() {
        CircularQueue<Integer> queue = builder.get();
        assertTrue("constructor creates an empty queue", queue.empty());
    }
    @Test
    public void notEmptyAfterEnqueue() {
        CircularQueue<Integer> queue = builder.get();
        queue.enqueue(5);
        assertFalse("not empty after enqueue", queue.empty());
    }
    @Test
    public void enqueueOnceAndDequeue() {
        CircularQueue<Integer> queue = builder.get();
        queue.enqueue(0);
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        assertEquals("Should be 0", new Integer(0), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());
        assertEquals("Should be 1", new Integer(1), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());
        assertEquals("Should be 2", new Integer(2), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());
        assertEquals("Should be 3", new Integer(3), queue.dequeue());
        assertTrue("Empty queue", queue.empty());
    }
    @Test
    public void enqueueAndDequeue() {
        CircularQueue<Integer> queue = builder.get();
        queue.enqueue(0);
        queue.enqueue(1);
        assertEquals("Should be 0", new Integer(0), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());

        queue.enqueue(2);
        assertEquals("Should be 1", new Integer(1), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());

        queue.enqueue(3);
        queue.enqueue(4);
        queue.enqueue(5);
        assertEquals("Should be 2", new Integer(2), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());
        assertEquals("Should be 3", new Integer(3), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());
        assertEquals("Should be 4", new Integer(4), queue.dequeue());
        assertFalse("Not empty queue", queue.empty());
        assertEquals("Should be 5", new Integer(5), queue.dequeue());
        assertTrue("Empty queue", queue.empty());
    }

    private void enqueueBoth(Queue<Integer> jQueue, CircularQueue<Integer> queue, int v) {
        jQueue.add(v);
        queue.enqueue(v);
    }
    private boolean dequeueBoth(Queue<Integer> jQueue, CircularQueue<Integer> queue) {
        return jQueue.poll().equals(queue.dequeue());
    }

    @Test
    public void largeTest() {
        Queue<Integer> jQueue = new ArrayDeque<>();
        CircularQueue<Integer> queue = builder.get();

        enqueueBoth(jQueue, queue, 0);
        enqueueBoth(jQueue, queue, 1);
        enqueueBoth(jQueue, queue, 2);
        assertTrue(dequeueBoth(jQueue, queue));
        assertTrue(dequeueBoth(jQueue, queue));

        enqueueBoth(jQueue, queue, 3);
        enqueueBoth(jQueue, queue, 4);
        enqueueBoth(jQueue, queue, 5);
        enqueueBoth(jQueue, queue, 6);
        assertTrue(dequeueBoth(jQueue, queue));

        enqueueBoth(jQueue, queue, 7);
        enqueueBoth(jQueue, queue, 8);
        assertTrue(dequeueBoth(jQueue, queue));
        assertTrue(dequeueBoth(jQueue, queue));

        for (int i = 0 ; i != 1024 ; ++i) {
            enqueueBoth(jQueue, queue, i*i);
        }
        while (! jQueue.isEmpty()) {
            assertTrue(dequeueBoth(jQueue, queue));
        }
    }

    @Parameterized.Parameters(name = "{0}")
    public static Collection<Object[]> params() {
        Object[][] ps = {
                new Object[] { "Singly linked list", CircularQueueFactory.builderCircularQueue() },
                new Object[] { "Resizable array", CircularQueueFactory.builderCircularQueueArray() }
        };
        return Arrays.asList(ps);
    }
}