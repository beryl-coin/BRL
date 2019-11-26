// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2019 The Beryl Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "governance-votedb.h"

CGovernanceObjectVoteFile::CGovernanceObjectVoteFile()
    : nMemoryVotes(0),
      listVotes(),
      mapVoteIndex()
{}

CGovernanceObjectVoteFile::CGovernanceObjectVoteFile(const CGovernanceObjectVoteFile& other)
    : nMemoryVotes(other.nMemoryVotes),
      listVotes(other.listVotes),
      mapVoteIndex()
{
    RebuildIndex();
}

void CGovernanceObjectVoteFile::AddVote(const CGovernanceVote& vote)
{
    uint256 nHash = vote.GetHash();
    // make sure to never add/update already known votes
    if (HasVote(nHash))
        return;
    listVotes.push_front(vote);
    mapVoteIndex.emplace(nHash, listVotes.begin());
    ++nMemoryVotes;
}

bool CGovernanceObjectVoteFile::HasVote(const uint256& nHash) const
{
    return mapVoteIndex.find(nHash) != mapVoteIndex.end();
}

bool CGovernanceObjectVoteFile::SerializeVoteToStream(const uint256& nHash, CDataStream& ss) const
{
    vote_m_cit it = mapVoteIndex.find(nHash);
    if(it == mapVoteIndex.end()) {
        return false;
    }
    ss << *(it->second);
    return true;
}

std::vector<CGovernanceVote> CGovernanceObjectVoteFile::GetVotes() const
{
    std::vector<CGovernanceVote> vecResult;
    for(vote_l_cit it = listVotes.begin(); it != listVotes.end(); ++it) {
        vecResult.push_back(*it);
    }
    return vecResult;
}

void CGovernanceObjectVoteFile::RemoveVotesFromMasternode(const COutPoint& outpointMasternode)
{
    vote_l_it it = listVotes.begin();
    while(it != listVotes.end()) {
        if(it->GetMasternodeOutpoint() == outpointMasternode) {
            --nMemoryVotes;
            mapVoteIndex.erase(it->GetHash());
            listVotes.erase(it++);
        }
        else {
            ++it;
        }
    }
}

void CGovernanceObjectVoteFile::RebuildIndex()
{
    mapVoteIndex.clear();
    nMemoryVotes = 0;
    vote_l_it it = listVotes.begin();
    while(it != listVotes.end()) {
        CGovernanceVote& vote = *it;
        uint256 nHash = vote.GetHash();
        if(mapVoteIndex.find(nHash) == mapVoteIndex.end()) {
            mapVoteIndex[nHash] = it;
            ++nMemoryVotes;
            ++it;
        }
        else {
            listVotes.erase(it++);
        }
    }
}
