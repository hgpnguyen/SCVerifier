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
        x = simple();
    }

    function simple() public pure returns(uint) {
        return 5;
    }

    function unsat() public pure returns (uint) {
        uint a; uint b;
        uint c;
        a = a + 10 - b * 25;
        b += getInt() - 10 / 2;
        c = 104;
        add();
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
        if (getBool()) {
           b = 10;
        }
        if (c > hex'10FA') {
            b = 5;
        }
        for(int a = 0; a < 10; ++a) {
            b += 1;
        }
    }

    function getInt() public pure returns(uint) {
        uint a;
        a = 10 * 5;
        return a;
    }
    function getBool() public pure returns(bool) {
        return true;
    }
}