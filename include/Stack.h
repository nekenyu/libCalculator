/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef  STACK_H
#define  STACK_H

#ifndef RESULT_H
#include "Result.h"
#endif // RESULT_H

namespace Calculator {
  
  class StackItem;
  class StackIteratorPimpl;
  class StackPimpl;
  class VariableSet;

  /*
   * StackIterator
   */

  /** \class StackIterator 
   * \brief Iterator over a Stack from top to bottom
   */
  class StackIterator {
  private:
    typedef std::shared_ptr<StackIteratorPimpl> PimplPtr;

  public:
    /** Equivalent of StackItem::Ptr; */
    typedef std::shared_ptr<StackItem> StackItemPtr;

    /** Hint for accessing the value at an iterator */
    enum class Hint {
      /** Dereference the next read */
      DEREFERENCE_NEXT,
	/** Do not dereference the next read */
	NO_DEREFERENCE_NEXT
	};
    
    ~StackIterator() = default;
    
    /** Create with reference to the variables and the implementint iterator.
     *
     * @param thePimpl initial data for the StackIterator
     */
    StackIterator(std::shared_ptr<StackIteratorPimpl> thePimpl);
    
    StackIterator() = delete;
    StackIterator(const StackIterator&);
    StackIterator(StackIterator&&) = default;
    StackIterator& operator=(const StackIterator&);
    StackIterator& operator=(StackIterator&&) = default;
    
    /** Pre-increment: Move to the next position away from the top.
     *
     * @return this iterator
     */
    StackIterator& operator++();
    
    /** Post-increment: Move to the next position away from the top, but return the
     * a copy of this iterator without the modification.
     *
     * @return a copy of this iterator before the increment.
     */
    StackIterator operator++(int);
    
    /** Return true if this iterator is the same position as rhs.
     * 
     * @param rhs to compare this iterator to
     *
     * @return true if this iterator and rhs refer to the same position, otherwise
     * false
     */
    bool operator==(const StackIterator& rhs) const;
    
    /** Return true if this iterator is not the same position as rhs.
     * 
     * @param rhs to compare this iterator to
     *
     * @return false if this iterator and rhs refer to the same position, otherwise
     * true
     */
    bool operator!=(const StackIterator& rhs) const;

    /** @return false if any errors have been reported, otherwise true */
    operator bool() const;

    /** @return the object at the current position as per the current hint and reset
     * the hint for the next read to Hint::DEREFERENCE_NEXT
     */
    StackItemPtr operator*();
    
    /** @return the current item without dereferencing, ignoring the hint entirely
     */
    StackItemPtr noDereference();
    
    /** Set the current hint for reading the value to theHint.
     *
     * @param theHint to set the hint for the next read to
     *
     * @return this iterator
     */
    StackIterator& setHint(Hint theHint);
    
    /** Convenience method to read the current value by operator->* (respecting the
     * current hint) and return it to a T::Ptr by std::dynamic_pointer_cast.  If
     * the cast fails, the returned value is empty
     *
     * @tparam T desired type to cast the value to
     * @param required if true, conversion failure is logged as a positional
     * message in the Result.
     *
     * @return the current value from operator* as a T::Ptr, which may be empty if
     * the cast failed
     */
    template<typename T>
      auto as(bool required = true) -> typename T::Ptr {
      typename T::Ptr asT = std::dynamic_pointer_cast<T, StackItem>(this->operator*());
      if(required && !asT) {
	addError(std::string("Value is not ") + T::indef_type_string());
      }
      return asT;
    }
    
    /** @return Errors, such as conversion and variable, thus far, if any */
    const Result& getResult() const;

    /** Add error message at position
     *
     * @param position in the stack the error occurred
     * @param message describing the error
     */
    void addError(unsigned int position, const std::string& message);

    /** Add error message at current position
     *
     * @param message describing the error
     */
    void addError(const std::string& message);
    
    /** @return the private implementation */
    PimplPtr getPimpl();

  private:
    /** The private implementation */
    PimplPtr pimpl;
  };
  
  /** Set the iter's hint and return the iter.
   *
   * @param iter to set hint on
   * @param hint to set
   *
   * @return iter
   */
  StackIterator& operator>>(StackIterator& iter, StackIterator::Hint hint);
  
  /** Set t to *iter and return iter.
   *
   * @param iter to read from
   * @param t to set *iter into
   *
   * @return iter
   */
  StackIterator& operator>>(StackIterator& iter, std::shared_ptr<StackItem>& t);
  
  /** Convenience function to read the current value of iter by the template as()
   * (respecting the current hint) and set to t. If the cast fails in t, the set
   *  value is empty
   *
   * @tparam T desired type to cast the value to
   *
   * @param iter to read from
   * @param t to set iter.as<T>() into
   *
   * @return iter
   */
  template<typename T>
    StackIterator& operator>>(StackIterator& iter, T& t) {
    t = iter.template as<typename T::element_type>();
    ++iter;
    return iter;
  }
  
  /* 
   * Stack
   */
    
  /** Stack of values to process from.
   *
   * Contains StackItem::Ptr objects.
   *
   * \todo Provide load / save operations.
   * Provide the ability to write and read Calculator.txt files which will
   * restore the existing state.
   */
  class Stack {
  private:
    typedef std::shared_ptr<StackPimpl> PimplPtr;
    typedef std::shared_ptr<StackItem> StackItemPtr;

  public:
    /** Count of StackItems */
    typedef unsigned int Count;
    
    Stack();
    Stack(const Stack& rhs) = delete;
    Stack(Stack&& rhs) = delete;
    Stack& operator=(const Stack& rhs) = delete;
    Stack& operator=(Stack&& rhs) = delete;
    
    /** @return number of StackItems on the Stack */
    Count getDepth() const;

    /** @return the VariableSet */
    VariableSet& getVariables();

    /** Reset the stack including pop all variables and reset the variables */
    void reset();

    /** Pop all items from the stack */
    void popAll();

    /** @return StackIterator at the top of the Stack
     *
     * \note This should be a const method; however, the underlying
     * implementation (STL) would only provide a const_iterator.  This would be
     * just fine for its use; however, std::vector::erase requires a non-const
     * iterator, which means this must be non-const.  I could const cast around
     * this, but I'll go simpler.
     */
    StackIterator begin();

    /** @return StackIterator after the bottom of the Stack
     *
     * \note This should be a const method; however, the underlying
     * implementation (STL) would only provide a const_iterator.  This would be
     * just fine for its use; however, std::vector::erase requires a non-const
     * iterator, which means this must be non-const.  I could const cast around
     * this, but I'll go simpler.
     */
    StackIterator end();

    /** Pop all items after iter on the Stack */
    void popAfter(StackIterator& iter);

    /** Push item onto the stack
     *
     * @param item to push
     */
    void push(StackItemPtr item);

    /** Create string representation of the current contents of the Stack */
    std::string toString() const;

  private:
    /** The Private Implementation */
    PimplPtr pimpl;
  };
  
} // namespace Calculator

#endif //  STACK_H
