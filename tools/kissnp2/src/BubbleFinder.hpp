/*****************************************************************************
 *   GATB : Genome Assembly Tool Box
 *   Copyright (C) 2014  INRIA
 *   Authors: P.Peterlongo, R.Uricary, R.Chikhi, G.Rizk, E.Drezen
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef _BUBBLE_HPP_
#define _BUBBLE_HPP_

/********************************************************************************/

#include <cstdlib>
#include <cmath>
#include <gatb/gatb_core.hpp>

/********************************************************************************/
#define STR_DISCOSNP_LOW_COMPLEXITY          "-l"
#define STR_DISCOSNP_AUTHORISED_BRANCHING    "-b"
#define STR_DISCOSNP_WITH_EXTENSION          "-e"

/********************************************************************************/
template<size_t span=KSIZE_1>
class BubbleFinder : public Algorithm
{
public:

    /** Shortcuts. */
    typedef typename Kmer<span>::Model Model;
    typedef typename Kmer<span>::Type  kmer_type;

    /** Constructor. */
    BubbleFinder (const Graph& graph, IProperties* input);

    /** Destructor. */
    ~BubbleFinder ();

    /** */
    void execute ();

    /** */
    void start (const Node& node);

protected:

    /** */
    void expand (
        int pos,
        char* path1,
        char* path2,
        const kmer_type& kmer1,
        const kmer_type& kmer2,
        const kmer_type& previous_kmer1,
        const kmer_type& previous_kmer2
    );

    const Graph& graph;
    Model        modelMin;
    Model        modelDirect;

    size_t sizeKmer;
    int threshold;

    IBank* _outputBank;
    void setOutputBank (IBank* outputBank)  { SP_SETATTR(outputBank); }

    int low;
    int authorised_branching;

    bool extend_snps;
    bool print_extensions;
    bool strict_extension; // true: strict extension, fales: contig extension
    int  min_size_extension;
    
    /** We need a synchronizer for dumping the sequences into the output bank. */
    ISynchronizer* _synchronizer;
    void setSynchronizer (ISynchronizer* synchronizer)  { SP_SETATTR(synchronizer); }

    size_t nb_bubbles;
    size_t nb_bubbles_high;
    size_t nb_bubbles_low;

    /**
     * Extends if necessary left and/or right parts of the bubble.
     * Prints results
     * path1 and path2: character pathes (no binary format). Of length 2k-1, 2k, or 2k+1, depending ont the results of "close_snps"
     * score=complexity score
     * where_to_extend : 0=nothing, 1=left only, 2=right only, 3=both
     */
    //extension==0 no extension, =1 only left, =2 only right, =3 both
    void retrieveSequence (char* path, const char* type, int score, int where_to_extend, size_t seqIndex, Sequence& seq);

    bool two_possible_extensions_on_one_path(kmer_type) const;
    bool two_possible_extensions(kmer_type kmer1, kmer_type kmer2) const;

    //returns -1 not closed, 0 no unique extension, 1 only left, 2 only right, 3 both
    virtual int close_snp (const char * path1, const char * path2, char * path1_c, char * path2_c);

    virtual void addExtraCommentInformation (
        std::stringstream& ss,
        std::pair<char*,int> left_extension,
        std::pair<char*,int> right_extension,
        int where_to_extend
    );

    bool checkKmersDiff (const kmer_type& previous, const kmer_type& current, const kmer_type& next) const;

    // Check whether the first kmer of the first path is smaller than the first kmer of the revcomp(first path),
    // this should avoid repeated SNPs
    bool checkPath (char* path) const;

    bool checkBranching (kmer_type kmer1, kmer_type kmer2) const;

    bool checkLowComplexity (char* path1, char* path2, int& score) const;
};

/********************************************************************************/

template<size_t span=KSIZE_1>
class BubbleFinderWithExtension : public BubbleFinder<span>
{
public:

    /** Constructor. */
    BubbleFinderWithExtension (const Graph& graph, IProperties* input);

    /** Destructor. */
    ~BubbleFinderWithExtension ();

protected:

    virtual int close_snp (const char * path1, const char * path2, char * path1_c, char * path2_c);
};

/********************************************************************************/

#endif // _BUBBLE_HPP_