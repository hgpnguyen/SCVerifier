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
        if(true)
            x = x + 1;
        x = x + 1;
    }

    function unsat() public pure returns (uint) {
        uint a; uint b;
        uint c;
        a = a + 10 - b * 25;
        b += a - 10 / 2;
        c = 104;
        if(c == 20)
            a = a + 5;
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