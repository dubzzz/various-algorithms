import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * Created by Nicolas DUBIEN on 04/03/2017.
 *
 * input:  expression without left parenthesis
 * output: equivalent infix expression with the parentheses inserted
 *
 * assumptions:
 * - input is a valid expression
 * - you can assume that operators, numbers and right parentheses are separated by one and only one space character
 * - no priority between operators
 * - possible operators are: +, -, * and /
 *
 * Taken from Algorithms Fourth Edition
 * from Robert Sedgewick and Kevin Wayne
 */
public class EquivalentInfixExpression {
    public static String dijkstraTwoStacks(String input) {
        Stack<String> ops = new Stack<>();
        Stack<String> nums = new Stack<>();
        String[] partialLexems = input.split(" ");
        for (String lx : partialLexems) {
            if (lx.equals(")")) {
                String lastNum = nums.pop();
                nums.push("( " + nums.pop() + " " + ops.pop() + " " + lastNum + " )");
            }
            else if (lx.equals("+") || lx.equals("-") || lx.equals("*") || lx.equals("/")) {
                ops.add(lx);
            }
            else {
                nums.add(lx);
            }
        }
        if (! ops.empty()) {
            String lastNum = nums.pop();
            nums.push(nums.pop() + " " + ops.pop() + " " + lastNum);
        }
        return nums.empty() ? "" : nums.pop();
    }
}
