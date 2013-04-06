/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef RESULT_H
#define RESULT_H

namespace Calculator {
  
  /** Collection of Result information for an operation.
   *
   * Contains non-positional message strings for things like "Ok".  May be used
   * by driving code to pass around commands like "quit".
   *
   * Contains positional messages of stack position (0 is top) and message to
   * indicate what failed, such as Stack Underflow or conversion error on a
   * position in the stack.
   */
  class Result {
  public:
    typedef std::string Message;
    typedef std::vector<Message> Messages;

    /** For convenience, we use a pair for the line and message for a position */
    typedef std::pair<unsigned int, std::string> PositionMessage;
    typedef std::vector<PositionMessage> PositionMessages;
    
    Result() = default;

    /** Create with all messages in theMessage */
    Result(std::initializer_list<Message> theMessages);

    /** Create with all the positional messages in thePositionMessages */
    Result(std::initializer_list<PositionMessage> thePositionMessages);

    /** Create with all messages in theMessage and all the positional messages
     * in thePositionMessages.
     */
    Result(std::initializer_list<Message> theMessages,
      std::initializer_list<PositionMessage> thePositionMessages);

    /** @return all the messages for iteration */
    const Messages& getMessages() const;

    /** Convenience to test with message has been set
     *
     * @param message to test
     *
     * @return true if the message is present, otherwise false
     */
    bool hasMessage(const std::string& message) const;

    /** Add message.
     *
     * @param message to add
     */
    void addMessage(const std::string& message);

    /** @return all the positional messages for iteration */
    const PositionMessages& getPositionMessages() const;

    /** Convenience to test if the positional message has been set at the position
     *
     * @param position to look for message in
     * @param message to look for in position
     *
     * @return true if the message is present at position, otherwise false
     */
    bool hasPositionMessage(const unsigned int position, const std::string& message) const;
    
    /** Add the positional message
     *
     * @param position the message belongs to
     * @param message to be added at position
     */
    void addPositionMessage(const unsigned int position, const std::string& message);

    /** @return a string representation of this Result */
    std::string toString() const;

    /** Create a string representation of this Result with prefix at the start
     * of each line.
     *
     * @param prefix to put before each line
     *
     * @return string representation
     */
    std::string toString(const std::string& prefix) const;

  private:
    /** All messages */
    Messages messages;

    /** All positional messages */
    PositionMessages positionMessages;
  };
  
} // namespace Calculator 

#endif // RESULT_H
