## Runoff

This program is modelled after the US runoff election system; a ranked-choice voting system.
This allows votes to vote for more than one candidate, and the candidates are ranked in order of personal preference.

A candidate can only win if the he/she possesses more than majority(50%) of first preference votes.

If no candidates has more than 50% of votes, the candidate with the lowest amount of votes will be eliminated each round of the election.

#### Example 
Candidates: Ron, Hermoine, Harry

Number of votes: 3

</br>

***./runoff Ron Hermoine Harry***

***Rank 1: Hermoine***

***Rank 2: Harry***

***Rank 3: Ron***

</br>

***Rank 1: Hermoine***

***Rank 2: Ron***

***Rank 3: Harry***

</br>

***Rank 1: Hermoine***

***Rank 2: Harry***

***Rank 3: Ron***

</br>

Winner: **Hermoine**
