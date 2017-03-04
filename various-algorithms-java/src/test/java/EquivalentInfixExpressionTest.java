import org.junit.Test;
import static org.junit.Assert.*;

/**
 * Created by Nicolas DUBIEN on 04/03/2017.
 */
public class EquivalentInfixExpressionTest {
    @Test
    public void noParenthesisOneNumber() {
        assertEquals("One number expression keep the same", "42", EquivalentInfixExpression.apply("42"));
    }
    @Test
    public void noParenthesisOneOperation() {
        assertEquals("No parenthesis keep the same", "1 + 2", EquivalentInfixExpression.apply("1 + 2"));
    }
    @Test
    public void missingFirstParenthesis() {
        assertEquals("Add start parenthesis", "( 1 + 2 )", EquivalentInfixExpression.apply("1 + 2 )"));
    }
    @Test
    public void missingMultipleParentheses() {
        assertEquals("Add missing parentheses", "( ( 1 + 2 ) * ( ( 3 - 4 ) * ( 5 - 6 ) ) )", EquivalentInfixExpression.apply("1 + 2 ) * 3 - 4 ) * 5 - 6 ) ) )"));
    }
}