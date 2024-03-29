pragma solidity ^0.4.24;
contract Puzzle {
    address public owner;
    bool public locked;
    uint public reward;
    bytes32 public diff;
    bytes public solution;

    function Puzzle() {
        owner = msg.sender;
        reward = msg.value;
        locked = false;
        diff = bytes32(11111);
    }

    function(){
        if (msg.sender == owner) {
            if (locked)
                throw;
            owner.send(reward);
            reward = msg.value;
        }
        else if (msg.data.length > 0) {
            if (locked) throw;
            if (sha256((msg.data)) < diff) {
                msg.sender.send(reward);
                solution = msg.data;
                locked = true;
            }
        }
    }

}