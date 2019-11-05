pragma solidity ^0.5.0;

contract MyContract {
    struct StructType {
        uint[] contents;
        uint moreInfo;
    }
    StructType s;

    function add() public pure {
        uint y;
        uint x;
        y = 0;
        x = y + 1;
        x = x + 1;
        x = x + 1;
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