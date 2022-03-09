// HugeInt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


class HugeInt {

    struct Node {
        int value;
        Node* next;
    };
    struct HugeIntNode {
        HugeInt* value;
        HugeIntNode* next;
    };

    Node* _head;
    bool isNegative;
public:
    HugeInt(int value) {
        if (value < 0) {
            isNegative = true;
            value *= -1;
        }
        _head = new Node();
        _head->value = value % 10;
        _head->next = 0;
        if (value / 10 > 0) {
            Node* current = _head;
            while (value / 10 > 0) {
                value /= 10;
                current->next = new Node();
                current->next->value = value % 10;
                current = current->next;
            }
        }
    }
    HugeInt(std::string value) {
        _head = new Node();

        Node* current = _head;
        int i = 0;
        int endPoint = 0;
        while (value[i] != '\0')
            i++;

        i--;

        
        if (value[0] == '-') {
            isNegative = true;
            endPoint = 1;
        }
        while (i >= endPoint) {
            current->value = (int)value[i] - '0';
            if (i > endPoint) {
                current->next = new Node();
                current = current->next;
            }
            i--;
        }
    }
    HugeInt operator + (const HugeInt& arg) const {
        HugeInt hi(0);
        Node* ourNumber = hi._head;
        Node* current = _head;
        Node* otherCurrent = arg._head;
        int sum = 0;
        int carry = 0;
        while (current != 0 || otherCurrent != 0 || carry > 0) {
            int operand1 = (current != 0) ? current->value : 0;
            int operand2 = (otherCurrent != 0) ? otherCurrent->value : 0;
            sum = (operand1 + operand2 + carry) % 10;
            ourNumber->value = sum;
            carry = (operand1 + operand2 + carry) / 10;
            if (current != 0)
                current = current->next;
            if (otherCurrent != 0)
                otherCurrent = otherCurrent->next;
            if (current != 0 || otherCurrent != 0 || carry > 0) {
                ourNumber->next = new Node();
                ourNumber->next->value = carry;
                ourNumber = ourNumber->next;
            }
        }
        return hi;
    }
    HugeInt operator * (const HugeInt& arg) const {
        HugeIntNode* hiNodeHead = new HugeIntNode();
        HugeIntNode* hiNode = hiNodeHead;
        HugeInt result(0);
        Node* operand2Node = arg._head;
        int carry = 0;
        int zeroCount = 0;
        while (operand2Node != 0) {
            Node* operand1Node = _head;
            HugeInt* newOperand = new HugeInt(0);
            Node* newOperandNums = newOperand->_head;
            for (int i = 0; i < zeroCount; i++) {
                newOperandNums->value = 0;
                newOperandNums->next = new Node();
                newOperandNums = newOperandNums->next;
            }
            while (operand1Node != 0) {
                int operand1 = operand1Node->value;
                int operand2 = operand2Node->value;
                int prod = ((operand1 * operand2) + carry) % 10;
                newOperandNums->value = prod;
                carry = ((operand1 * operand2) + carry) / 10;
                operand1Node = operand1Node->next;
                if (operand1Node != 0 || carry > 0) {
                    newOperandNums->next = new Node();
                    newOperandNums->next->value = carry;
                    newOperandNums = newOperandNums->next;
                }
            }
            hiNode->value = newOperand;
            operand2Node = operand2Node->next;
            if (operand2Node != 0) {
                hiNode->next = new HugeIntNode();
                hiNode = hiNode->next;
            }
            zeroCount++;
        }
        while (hiNodeHead != 0) {
            result = result + *hiNodeHead->value;
            hiNodeHead = hiNodeHead->next;
        }
        if ((isNegative && !arg.isNegative) || (!isNegative && arg.isNegative))
            result.isNegative = true;
        return result;
    }


    friend std::ostream& operator << (std::ostream& out, HugeInt& ob) {
        Node* current = ob._head;
        if (ob.isNegative)
            out << "-";
        printNum(out, current);
        return out;
    }


    static void printNum(std::ostream& out, Node* node) {
        if (node != 0)
            printNum(out, node->next);
        if (node != 0)
            out << node->value;
    }
};

int main()
{
    HugeInt hi1("-12345");
    HugeInt hi2(-312);
    std::cout << "Number 1: " << hi1 << std::endl;
    std::cout << "Number 2: " << hi2 << std::endl;
    HugeInt hi3 = hi1 + hi2;
    HugeInt hi4 = hi1 * hi2;
    std::cout << hi1 << " + " << hi2 << " = " << hi3 << std::endl;
    std::cout << hi1 << " * " << hi2 << " = " << hi4 << std::endl;
}