$:.unshift './'
require "foo"

describe 'Foo' do
  describe Test do
    let(:uri) { '/home/sozontov/projects/ezags-client/public/WSDL/rZAGS/InquiryService.xsd' }
    let(:namespace) { 'http://ezags.rt.ru/rzags/InquiryService/type/' }
    subject { Test.new uri }

    it 'should has uri' do
      subject.should respond_to :uri
      subject.uri.should eql uri
    end

    it 'should has namespace' do
      subject.should respond_to :namespace
      subject.namespace.should eql namespace
    end

    it { should respond_to :instance }

    it 'should generate xml' do
      subject.instance.should be_a String
      subject.instance.should eql "<?xml version='1.0' encoding='UTF-8' standalone='no' ?><s:getPerformanceStateInquiry xmlns:s=\"http://ezags.rt.ru/rzags/InquiryService/type/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><s:inquiryIdentifier></s:inquiryIdentifier></s:getPerformanceStateInquiry>"
    end

  end
end