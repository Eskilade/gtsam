/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    GaussianFactor.h
 * @brief   A factor with a quadratic error function - a Gaussian
 * @brief   GaussianFactor
 * @author  Richard Roberts, Christian Potthast
 */

// \callgraph

#pragma once

#include <gtsam/inference/IndexFactor.h>

#include <string>
#include <utility>

namespace gtsam {

  // Forward declarations
  class VectorValues;
  class Permutation;
  class GaussianConditional;
  template<class C> class BayesNet;

  /**
   * An abstract virtual base class for JacobianFactor and HessianFactor.
   * A GaussianFactor has a quadratic error function.
   * GaussianFactor is non-mutable (all methods const!).
   * The factor value is exp(-0.5*||Ax-b||^2)
   */
  class GaussianFactor: public IndexFactor {

  protected:

    /** Copy constructor */
    GaussianFactor(const This& f) : IndexFactor(f) {}

    /** Construct from derived type */
    GaussianFactor(const GaussianConditional& c);

    /** Constructor from a collection of keys */
    template<class KeyIterator> GaussianFactor(KeyIterator beginKey, KeyIterator endKey) :
        Base(beginKey, endKey) {}

    /** Default constructor for I/O */
    GaussianFactor() {}

    /** Construct unary factor */
    GaussianFactor(Index j) : IndexFactor(j) {}

    /** Construct binary factor */
    GaussianFactor(Index j1, Index j2) : IndexFactor(j1, j2) {}

    /** Construct ternary factor */
    GaussianFactor(Index j1, Index j2, Index j3) : IndexFactor(j1, j2, j3) {}

    /** Construct 4-way factor */
    GaussianFactor(Index j1, Index j2, Index j3, Index j4) : IndexFactor(j1, j2, j3, j4) {}

    /** Construct n-way factor */
    GaussianFactor(const std::set<Index>& js) : IndexFactor(js) {}

    /** Construct n-way factor */
    GaussianFactor(const std::vector<Index>& js) : IndexFactor(js) {}

    /** Construct n-way factor */
    GaussianFactor(const FastVector<Index>& js) : IndexFactor(js) {}

  public:

    typedef GaussianConditional ConditionalType;
    typedef boost::shared_ptr<GaussianFactor> shared_ptr;

    // Implementing Testable interface
    virtual void print(const std::string& s = "") const = 0;
    virtual bool equals(const GaussianFactor& lf, double tol = 1e-9) const = 0;

    virtual double error(const VectorValues& c) const = 0; /**  0.5*(A*x-b)'*D*(A*x-b) */

    /** Return the dimension of the variable pointed to by the given key iterator */
    virtual size_t getDim(const_iterator variable) const = 0;

    /** Clone a factor (make a deep copy) */
    virtual GaussianFactor::shared_ptr clone() const = 0;

    /**
     * Permutes the GaussianFactor, but for efficiency requires the permutation
     * to already be inverted.  This acts just as a change-of-name for each
     * variable.  The order of the variables within the factor is not changed.
     */
    virtual void permuteWithInverse(const Permutation& inversePermutation) = 0;

  private:
    /** Serialization function */
    friend class boost::serialization::access;
    template<class ARCHIVE>
    void serialize(ARCHIVE & ar, const unsigned int version) {
    	ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(IndexFactor);
    }

  }; // GaussianFactor

  /** make keys from list, vector, or map of matrices */
	template<typename ITERATOR>
	static FastVector<Index> GetKeys(size_t n, ITERATOR begin, ITERATOR end) {
	  FastVector<Index> keys;
		keys.reserve(n);
		for (ITERATOR it=begin;it!=end;++it) keys.push_back(it->first);
		return keys;
	}

} // namespace gtsam
