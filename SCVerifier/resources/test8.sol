pragma solidity ^0.5.0;

contract MyContract {
    struct StructType {
        uint[] contents;
        uint moreInfo;
    }
    StructType s;
    uint global;
    uint y;
    mapping(address => mapping (address => uint))  map;

    constructor(uint in_) public {
        global = in_;
        map[address(this)][msg.sender] = 1 ether;
    }

    function() external payable {
        y = 0;
        y += 4;
    }

    function add() public {
        uint y;
        uint x;
        y = 2;
        x = y + 1;
        if(true)
            x = x + 1;
        x = x + 1;
        x = getInt();
        
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
        uint[] storage y = x; // works, assigns a pointer, data location of y is storage
        y[7]; // fine, returns the 8th element
        uint[3] memory g = [uint(1), 1, 4];
        uint[] memory t;
        uint k;
        g[1] += 5;
        k = g[2];
        delete x;
    }

    function mapTry(address guy) public returns(bool) {
        map[msg.sender][guy] = 7;
        return true;
    }
}