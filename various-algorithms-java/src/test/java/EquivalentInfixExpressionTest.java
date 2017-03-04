import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.util.Arrays;
import java.util.Collection;
import java.util.function.Function;

import static org.junit.Assert.assertEquals;

/**
 * Created by Nicolas DUBIEN on 04/03/2017.
 */
@RunWith(Parameterized.class)
public class EquivalentInfixExpressionTest {
    private final String implementationName;
    private final Function<String, String> algorithm;
    public EquivalentInfixExpressionTest(final String implementationName, final Function<String, String> algorithm) {
        this.implementationName = implementationName;
        this.algorithm = algorithm;
    }

    @Test
    public void noParenthesisOneNumber() {
        assertEquals("One number expression keep the same", "42", algorithm.apply("42"));
    }
    @Test
    public void noParenthesisOneOperation() {
        assertEquals("No parenthesis keep the same", "1 + 2", algorithm.apply("1 + 2"));
    }
    @Test
    public void missingFirstParenthesis() {
        assertEquals("Add start parenthesis", "( 1 + 2 )", algorithm.apply("1 + 2 )"));
    }

    @Test
    public void missingMultipleParentheses() {
        assertEquals("Add missing parentheses", "( ( 1 + 2 ) * ( ( 3 - 4 ) * ( 5 - 6 ) ) )", algorithm.apply("1 + 2 ) * 3 - 4 ) * 5 - 6 ) ) )"));
    }

    @Parameters(name = "{0}")
    public static Collection<Object[]> params() {
        Object[][] ps = {
                new Object[] { "Dijkstra two stacks", (Function<String, String>) EquivalentInfixExpression::dijkstraTwoStacks }
        };
        return Arrays.asList(ps);
    }
}