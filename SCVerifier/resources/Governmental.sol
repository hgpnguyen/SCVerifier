contract Governmental {
  address public owner;
  address public lastInvestor;
  uint public jackpot = 1 ether;
  uint public lastInvestmentTimestamp;
  uint public ONE_MINUTE = 1 minutes;

  constructor() public payable{
    owner = msg.sender;
    if (msg.value<1 ether) revert();
  }

  function invest() public payable{
    if (msg.value<jackpot/2) revert();
    lastInvestor = msg.sender;
    jackpot += msg.value/2;
    lastInvestmentTimestamp = block.timestamp;
  }

  function resetInvestment() public {
    if (block.timestamp < lastInvestmentTimestamp+ONE_MINUTE)
      revert();

    lastInvestor.send(jackpot);
    owner.send(this.balance-1 ether);

    lastInvestor = 0;
    jackpot = 1 ether;
    lastInvestmentTimestamp = 0;
  }
}