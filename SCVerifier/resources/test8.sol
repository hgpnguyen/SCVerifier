pragma solidity ^0.5.0;

contract MyContract {
    struct StructType {
        uint[] contents;
        uint moreInfo;
    }
    StructType s;

    function add() public pure returns (uint) {
        uint i; uint b;
        int f;
        int g = 10;
        uint len;
        bool a;
        if(!a)
            f = f + 5;
        else if (g < 5)
            f = f - 2;
        else f = 5;
        do{
            g = g + 1;
        } while (g < 15);
        if (i > b) {
            a = true;
        }
        return i;
    }

    function unsat() public pure returns (uint) {
        uint a; uint b;
        if ((a + 10 + b) < 0)
            b = 10;
        bool c; bool d;
        if (c || d && true)
            c = false;
        if (c && false)
            a = b + 8;
    }

    function Test() public pure {
        address a;
        bytes10 c;
        int b;
        string memory f = "dasdasd";
        if (a == address(0)) {
            b = 10;
        }
        if (c >= bytes8(uint64(10))) {
            b = 8;
        }
        if (true) {
           b = 10;
        }
        if (c > hex'10FA') {
            b = 5;
        }
    }
}