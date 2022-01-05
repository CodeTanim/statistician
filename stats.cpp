#include "stats.h"

#include <cassert>

using namespace std;

namespace main_savitch_2C {

  //Constructor 

  statistician::statistician() {

    m_len = 0; // length of sequence (# entries in sequence)
    m_sum = 0; // sum of all the numbers in the sequence

  }

  //Modification member functions:

  void statistician::next(double r) {

    // PreCondition: a double is passed by value to the function.
    // PostCondition: The value is assigned as a min, or a max. The sum of ALL the values passed are added up.
    // The amount of numbers passed by value is counted so it can be used to calculate the mean.

    //The if statement below checks for the first time, a value is passed. At this point the amount of numbers passed should be updated from zero to 1.
    // The mins and maxes should also be the same since there is only one number passed as value so far. The sum should also be updated to have that value. 
    if (m_len == 0) {

      m_min = r;
      m_max = r;
      m_len = 1;
      m_sum += r;

    }

    // The code below will activate once the function "next" has been called at least a second time. Which when 
    // it does we know m_len > 0 because of the assignment change to private variable m_len in the previous call. 
    // Each time the code below activates, m_len will increase by 1 and the value passed will be assigned as either a new max or a new min. 
    // The sum will also be appended with the r value that is passed. 
    else if (m_len > 0) {

      m_len++;

      // A number cannot be greater than the max AND smaller than the min. It has to be one or the other. 
      if (r > m_max) {

        m_max = r;
      }

      if (r < m_min) {

        m_min = r;
      }

      m_sum += r;

    }

    return;

  }

  // This function is to reset the statistican to a state where, it didn't contain any of the numbers.
  // So sum = 0 and the length = 0.  We do not need to change the min and max values because if the length is intitialzied to 0, then the first thing the "next" function 
  // will do when the reset statistician recieves a number is set both the min and max equal to that number. The first call to "next" for an empty statistician will always
  //  do that so we don't need to worry about accidentally comparing mins and maxes to the statistician before it was reset. 

  void statistician::reset() {
    //  Postcondition: The statistician has been cleared, as if no numbers had
    // yet been given to it.

    m_len = 0; // length of sequence (# entries in sequence)
    m_sum = 0; // sum of all the numbers in the statistician

  }

  // Constant member functions:

  int statistician::length() const {

    // Postcondition: The return value is the length of the sequence that has
    // been given to the statistician (i.e., the number of times that the
    // next(r) function has been activated).

    return m_len;
  }

  double statistician::sum() const {

    // Postcondition: Returns the sum of all the numbers that were passed to the statistician. 

    return m_sum;
  }

  double statistician::mean() const {

    // Precondition: the statistician must have at least one number passed to it and have the length updated to at least 1. It CANNOt be zero. 
    // Postcondition: Return the mean or average of all the numbers that were passed to the statistician. The function divides 
    // the sum of all the numbers by the length of the sequence.

    assert(length() > 0);

    return m_sum / double(m_len);
  }

  double statistician::minimum() const {

    // Precondition: the statistician must have at least one number passed to it and have the length updated to at least 1. It CANNOt be zero. 
    // Postcondition: The minimum value of the sequence of numbers passed to the statistician is returned.
    assert(length() > 0);

    return m_min;
  }

  double statistician::maximum() const {

    // Precondition: the statistician must have at least one number passed to it and have the length updated to at least 1. It CANNOt be zero. 
    // Postcondition: the maximum value of the sequence of numbers passed to the statistician is returned.

    assert(length() > 0);

    return m_max;
  }

  //Friend functions for operator overloading. 

  statistician operator + (const statistician & s1,
    const statistician & s2) {

    // Postcondition: The statistician that is returned contains all the
    // numbers of the sequences of s1 and s2.

    // If either s1 or s2 has no value passed to it or has zero length, then you return the other class because we would essentially be doing b + 0 = b. 
    // IF one of the statistician has nothing in it, then adding it with another statistician that does or doesn't have something will not change anything. 

    if (s1.length() == 0)
      return s2;
    if (s2.length() == 0)
      return s1;

    statistician result;

    // If both statisticians contain values, then you are treating the result statistician as if ALL the values from s1 and s2 were also passed through the result statistician.
    // The result statistician's values must reflect that behavior. So first we add up the sums of s1 and s2, then add up the lengths of s1 and s2.
    result.m_sum = s1.sum() + s2.sum();

    result.m_len = s1.length() + s2.length();

    // After that we compare the minimums and maximums of s1 and s2, and essentially find the absolute minimum and absolute maximum because keep in mind we are 
    // treating the result statistician as if ALL the values from s1 and s2
    // are passed through the result statistician so it had both of the minimums passed as well. But we don't need to store both minimums and maximums, 
    // we just compare and store the absolute minimums and maximums into the result statistician.

    if (s1.minimum() < s2.minimum()) {

      result.m_min = s1.minimum();
    } else {
      result.m_min = s2.minimum();
    }

    if (s1.maximum() > s2.maximum()) {

      result.m_max = s1.maximum();
    } else {

      result.m_max = s2.maximum();
    }

    return result;
  }

  statistician operator * (double scale,
    const statistician & s) {
    //Postcondition: The statistician that is returned contains the same
    // numbers that s does, but each number has been multiplied by the
    // scale number.

    statistician result;

    // If the object is empty, just return another empty object. Otherwise it will effect the assert checks
    // of max, min and mean which have a precondition of length() > 0 and those are functions being called in this operator. 
    if (s.length() == 0) {

      return result;
    }

    // Need to check for negative scalar number. If it is negative, then the product of the scale and the minimum of the 
    // statistician s being passed will become the maximum of the new statistician. Same rule applies to the maximum 
    // of s because when the maximum becomes negative, it will become the minimum of the new statistician.
    if (scale < 0) {

      result.m_min = scale * s.maximum();

      result.m_max = scale * s.minimum();

    } else {

      result.m_min = scale * s.minimum();

      result.m_max = scale * s.maximum();

    }

    // The sum's sign should change if there is negative scale and, the length should stay the same. 
    result.m_sum = scale * s.sum();
    result.m_len = s.length();

    return result;

  }

  //Other Operator overloading function (Non-member).
  bool operator == (const statistician & s1,
    const statistician & s2) {

    //  Postcondition: The return value is true if s1 and s2 have the zero
    //  length. Also, if the length is greater than zero, then s1 and s2 must
    //   have the same length, the same  mean, the same minimum, 
    //    the same maximum, and the same sum.

    // Sum, mean, length, min and max must all be equal for the two objects to be equal.

    if (s1.length() == 0 && s2.length() == 0) {

      return true;
    } else {

      return (s1.sum() == s2.sum()) && (s1.mean() == s2.mean()) && (s1.maximum() == s2.maximum()) && (s1.minimum() == s2.minimum()) && (s1.length() == s2.length());

    }
  }

}
