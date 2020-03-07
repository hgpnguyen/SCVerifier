pragma solidity ^0.5.0;

contract MyContract {
    struct StructType {
        uint[] contents;
        uint moreInfo;
    }
    StructType s;
    uint global;
    uint y;

    function add() public {
        uint y;
        uint x;
        y = 2;
        x = y + 1;
        if(true)
            x = x + 1;
        x = x + 1;
        x = simple();
        
    }

    function simple() public pure returns(uint) {
        return 5;
    }

    function unsat() public returns (uint) {
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
        int b = 0;
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
        for(int i = 0; i < 5; ++i) {
            b += 1;
        }
    }

    function getInt() public pure returns(uint) {
        (uint a, uint g) = (2, 5);
        a = 10 * 5;
        return a;
    }
    function getBool() public pure returns(bool) {
        return true;
    }
    uint[] x;
    function array(uint[] memory memoryArray) public {
        x = memoryArray; // works, copies the whole array to storage
        uint[] storage y = x; // works, assigns a pointer, data location of y is storage
        y[7]; // fine, returns the 8th element
        uint[3] memory g = [uint(1), 3, 4];
        uint[] memory t;
        delete x;
    }
}