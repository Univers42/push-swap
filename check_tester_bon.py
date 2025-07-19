#!/usr/bin/env python3
"""
Checker Integrity Tester
Validates sorting checker programs by testing 100 edge cases with random valid numbers
Compares output with reference checker_linux implementation
"""

import subprocess
import random
import sys
import os
from typing import List, Tuple

class CheckerTester:
    def __init__(self, checker_path: str = "./checker", reference_path: str = "./checker_linux"):
        self.checker_path = checker_path
        self.reference_path = reference_path
        self.test_cases = []
        self.results = []
        
    def generate_valid_unsorted_list(self, size: int) -> List[int]:
        """Generate a list that is definitely NOT sorted"""
        numbers = list(range(1, size + 1))
        
        # Ensure it's not sorted by doing specific shuffles
        while self.is_sorted(numbers):
            random.shuffle(numbers)
            
        # Additional guarantee - swap at least one adjacent pair
        if len(numbers) > 1:
            idx = random.randint(0, len(numbers) - 2)
            if numbers[idx] < numbers[idx + 1]:
                numbers[idx], numbers[idx + 1] = numbers[idx + 1], numbers[idx]
                
        return numbers
    
    def generate_sorted_list(self, size: int) -> List[int]:
        """Generate a sorted list"""
        return list(range(1, size + 1))
        
    def generate_reverse_sorted_list(self, size: int) -> List[int]:
        """Generate a reverse sorted list"""
        return list(range(size, 0, -1))
        
    def generate_duplicates_list(self, size: int) -> List[int]:
        """Generate a list with duplicates"""
        base = [random.randint(1, size) for _ in range(size)]
        return base
        
    def generate_single_element(self) -> List[int]:
        """Generate single element list"""
        return [random.randint(1, 100)]
        
    def generate_two_elements_unsorted(self) -> List[int]:
        """Generate two elements in wrong order"""
        a, b = random.randint(1, 50), random.randint(51, 100)
        return [b, a]  # Ensure b > a, so [b, a] is unsorted
        
    def is_sorted(self, lst: List[int]) -> bool:
        """Check if list is sorted"""
        return all(lst[i] <= lst[i + 1] for i in range(len(lst) - 1))
        
    def run_checker(self, numbers: List[int], program_path: str) -> str:
        """Run checker program with given numbers"""
        try:
            cmd = [program_path] + [str(n) for n in numbers]
            result = subprocess.run(cmd, 
                                  input="",  # Send empty input
                                  capture_output=True, 
                                  text=True, 
                                  timeout=5)
            if result.returncode != 0:
                stderr_msg = result.stderr.strip()
                # Don't treat as Error if it's just EOF-related
                if stderr_msg and "EOF" not in stderr_msg.lower():
                    return f"ERROR: {stderr_msg}"
            output = result.stdout.strip()
            # Extract just OK or KO from output if there's additional text
            lines = output.split('\n')
            for line in lines:
                line = line.strip()
                if line in ['OK', 'KO', 'Error']:
                    return line
                if line == "ERROR: Error":
                    return "Error"
            # If no clear OK/KO found, return the last non-empty line
            for line in reversed(lines):
                line = line.strip()
                if line:
                    if line == "ERROR: Error":
                        return "Error"
                    return line
            return output if output else "ERROR: No output"
        except subprocess.TimeoutExpired:
            return "ERROR: Timeout"
        except FileNotFoundError:
            return f"ERROR: Program not found at {program_path}"
        except Exception as e:
            return f"ERROR: {str(e)}"

    def run_checker_with_pipe(self, numbers: List[int], operations: str, program_path: str) -> str:
        """Run checker program with piped operations"""
        try:
            cmd = [program_path] + [str(n) for n in numbers]
            result = subprocess.run(cmd, 
                                  input=operations,
                                  capture_output=True, 
                                  text=True, 
                                  timeout=10)
            if result.returncode != 0:
                stderr_msg = result.stderr.strip()
                return f"ERROR: {stderr_msg}"
            output = result.stdout.strip()
            # Extract just OK or KO from output if there's additional text
            lines = output.split('\n')
            for line in lines:
                line = line.strip()
                if line in ['OK', 'ER']:
                    return line
                if line == "ERROR: Error":
                    return "Error"
            # If no clear OK/KO found, return the last non-empty line
            for line in reversed(lines):
                line = line.strip()
                if line:
                    if line == "ERROR: Error":
                        return "Error"
                    return line
            return output if output else "ERROR: No output"
        except subprocess.TimeoutExpired:
            return "ERROR: Timeout"
        except FileNotFoundError:
            return f"ERROR: Program not found at {program_path}"
        except Exception as e:
            return f"ERROR: {str(e)}"
    
    def generate_test_cases(self, num_cases: int = 100):
        """Generate comprehensive test cases"""
        self.test_cases = []
        
        # Test case categories
        categories = [
            ("Single element", lambda: self.generate_single_element()),
            ("Two unsorted", lambda: self.generate_two_elements_unsorted()),
            ("Small unsorted", lambda: self.generate_valid_unsorted_list(random.randint(3, 10))),
            ("Medium unsorted", lambda: self.generate_valid_unsorted_list(random.randint(11, 50))),
            ("Large unsorted", lambda: self.generate_valid_unsorted_list(random.randint(51, 100))),
            ("Sorted (should be OK)", lambda: self.generate_sorted_list(random.randint(3, 20))),
            ("Reverse sorted", lambda: self.generate_reverse_sorted_list(random.randint(3, 20))),
            ("With duplicates", lambda: self.generate_duplicates_list(random.randint(5, 30))),
        ]
        
        # Generate test cases
        cases_per_category = num_cases // len(categories)
        remaining = num_cases % len(categories)
        
        for i, (category, generator) in enumerate(categories):
            count = cases_per_category + (1 if i < remaining else 0)
            for _ in range(count):
                numbers = generator()
                # If there are duplicates, expect "Error"
                if len(numbers) != len(set(numbers)):
                    expected_result = "Error"
                else:
                    expected_result = "OK" if self.is_sorted(numbers) else "KO"
                self.test_cases.append({
                    'category': category,
                    'numbers': numbers,
                    'expected': expected_result,
                    'size': len(numbers)
                })
    
    def run_tests(self, use_pipe_mode: bool = False):
        """Run all test cases"""
        print(f"Running {len(self.test_cases)} test cases...")
        if use_pipe_mode:
            print("Using pipe mode with empty operations...")
        else:
            print("Using direct mode with EOF signal...")
        print("="*60)
        
        passed = 0
        failed = 0
        Errors = 0
        
        for i, test_case in enumerate(self.test_cases, 1):
            numbers = test_case['numbers']
            expected = test_case['expected']
            category = test_case['category']
            
            # Run your checker
            if use_pipe_mode:
                your_output = self.run_checker_with_pipe(numbers, "", self.checker_path)
                ref_output = self.run_checker_with_pipe(numbers, "", self.reference_path)
            else:
                your_output = self.run_checker(numbers, self.checker_path)
                ref_output = self.run_checker(numbers, self.reference_path)
            
            # Analyze results
            status = "UNKNOWN"
            
            # Handle reference checker not found case
            if "Program not found" in ref_output:
                # Only compare with expected result
                if "ERROR" in your_output:
                    status = "ERROR"
                    Errors += 1
                elif your_output == expected:
                    status = "PASS"
                    passed += 1
                else:
                    status = "FAIL"
                    failed += 1
            else:
                # Both programs available - compare them
                if "ERROR" in your_output and "ERROR" in ref_output:
                    # Both have Errors - check if they're the same
                    if your_output == ref_output:
                        status = "BOTH_ERROR_SAME"
                        # Don't count as Error if both programs fail the same way
                        # This might be expected behavior (e.g., rejecting duplicates)
                        passed += 1
                    else:
                        status = "BOTH_ERROR_DIFF"
                        failed += 1
                elif "ERROR" in your_output:
                    status = "YOUR_ERROR"
                    Errors += 1
                elif "ERROR" in ref_output:
                    status = "REF_ERROR"
                    # Your program works, reference doesn't - count as pass
                    if your_output == expected:
                        status = "PASS_REF_ERROR"
                        passed += 1
                    else:
                        status = "FAIL_REF_ERROR" 
                        failed += 1
                elif your_output == ref_output:
                    # Both programs agree
                    if your_output == expected:
                        status = "PASS"
                        passed += 1
                    else:
                        status = "BOTH_WRONG"
                        failed += 1
                else:
                    # Programs disagree
                    status = "MISMATCH"
                    failed += 1
            
            # Print detailed results for failures and important cases
            if status in ["FAIL", "MISMATCH", "YOUR_ERROR", "BOTH_ERROR_DIFF", "BOTH_WRONG", "FAIL_REF_ERROR"]:
                print(f"Test {i:3d}: {status}")
                print(f"  Category: {category}")
                print(f"  Input: {numbers[:10]}{'...' if len(numbers) > 10 else ''} (size: {len(numbers)})")
                print(f"  Expected: {expected}")
                print(f"  Your output: {your_output}")
                if ref_output != "ERROR: Program not found":
                    print(f"  Reference: {ref_output}")
                print(f"  Is sorted: {self.is_sorted(numbers)}")
                
                # Add explanation for specific cases
                if status == "BOTH_ERROR_SAME":
                    print(f"  Note: Both programs failed identically - may be expected behavior")
                elif status == "MISMATCH":
                    print(f"  Note: Programs disagree - this needs investigation!")
                print()
            elif status == "BOTH_ERROR_SAME" and i <= 5:
                # Show first few "both Error same" cases for analysis
                print(f"Test {i:3d}: {status} (Both programs reject this input identically)")
                print(f"  Category: {category}")
                print(f"  Input: {numbers[:10]}{'...' if len(numbers) > 10 else ''}")
                print(f"  Both output: {your_output}")
                print()
            elif i % 10 == 0:
                print(f"Completed {i} tests... ({passed} passed)")
        
        # Enhanced summary
        print("="*60)
        print("TEST SUMMARY:")
        print(f"Total tests: {len(self.test_cases)}")
        print(f"Passed: {passed}")
        print(f"Failed: {failed}")
        print(f"Errors (your program only): {Errors}")
        print(f"Success rate: {passed/len(self.test_cases)*100:.1f}%")
        
        # Check for actual differences between programs
        actual_differences = 0
        for i, test_case in enumerate(self.test_cases):
            numbers = test_case['numbers']
            if use_pipe_mode:
                your_out = self.run_checker_with_pipe(numbers, "", self.checker_path)
                ref_out = self.run_checker_with_pipe(numbers, "", self.reference_path)
            else:
                your_out = self.run_checker(numbers, self.checker_path)
                ref_out = self.run_checker(numbers, self.reference_path)
            
            if "Program not found" not in ref_out and your_out != ref_out:
                actual_differences += 1
        
        print(f"\nPROGRAM COMPARISON:")
        if "Program not found" in self.run_checker([1], self.reference_path):
            print("Reference checker not found - cannot compare programs")
        else:
            print(f"Cases where programs differ: {actual_differences}/{len(self.test_cases)}")
            if actual_differences == 0:
                print("⚠️  WARNING: Your checker and reference checker are IDENTICAL!")
                print("   This could mean:")
                print("   1. Your checker is perfect (unlikely)")  
                print("   2. You're testing the same program twice")
                print("   3. Both programs have the same bugs")
            else:
                print(f"✅ Programs differ in {actual_differences} cases - good for comparison")
        
        # Specific validation for the requirement
        print("\nVALIDATION CHECK:")
        unsorted_tests = [t for t in self.test_cases if not self.is_sorted(t['numbers'])]
        unsorted_expected_Error_count = 0
        failed_validations = []
        
        for idx, test_case in enumerate(unsorted_tests):
            if use_pipe_mode:
                your_output = self.run_checker_with_pipe(test_case['numbers'], "", self.checker_path)
            else:
                your_output = self.run_checker(test_case['numbers'], self.checker_path)
            # Expect "Error" if duplicates, else "KO"
            if len(test_case['numbers']) != len(set(test_case['numbers'])):
                expected_val = "Error"
                valid_Error = your_output == "Error"
            else:
                expected_val = "KO"
                valid_Error = your_output == expected_val
            if valid_Error:
                unsorted_expected_Error_count += 1
            else:
                failed_validations.append({
                    'numbers': test_case['numbers'],
                    'category': test_case['category'],
                    'output': your_output,
                    'size': len(test_case['numbers']),
                    'expected': expected_val
                })
        
        print(f"Unsorted lists that correctly returned expected value: {unsorted_expected_Error_count}/{len(unsorted_tests)}")
        
        if failed_validations:
            print(f"\n❌ VALIDATION FAILED: {len(failed_validations)} unsorted lists did NOT return expected value")
            print("\nFAILED VALIDATION CASES:")
            print("=" * 80)
            
            for i, case in enumerate(failed_validations, 1):
                print(f"Failed Case {i}:")
                print(f"  Category: {case['category']}")
                print(f"  Size: {case['size']}")
                print(f"  Numbers: {case['numbers']}")
                print(f"  Is sorted: {self.is_sorted(case['numbers'])}")
                print(f"  Expected: {case['expected']}")
                print(f"  Got: {case['output']}")
                
                has_duplicates = len(case['numbers']) != len(set(case['numbers']))
                if has_duplicates:
                    print(f"  ⚠️  Contains duplicates: {has_duplicates}")
                    duplicates = [x for x in set(case['numbers']) if case['numbers'].count(x) > 1]
                    print(f"  Duplicate values: {duplicates}")
                
                if "ERROR" in case['output']:
                    print(f"  🔍 Issue: Program returned Error instead of {case['expected']}")
                    if has_duplicates:
                        print(f"  💡 Likely cause: Checker rejects duplicates as invalid input")
                    else:
                        print(f"  💡 Likely cause: Other input validation Error")
                
                print()
            
            Error_cases = [c for c in failed_validations if "ERROR" in c['output']]
            duplicate_cases = [c for c in failed_validations if len(c['numbers']) != len(set(c['numbers']))]
            
            print("FAILURE ANALYSIS:")
            print(f"  Cases returning ERROR: {len(Error_cases)}/{len(failed_validations)}")
            print(f"  Cases with duplicates: {len(duplicate_cases)}/{len(failed_validations)}")
            
            if len(Error_cases) == len(failed_validations):
                print("  🎯 ALL failures are ERROR cases")
                if len(duplicate_cases) == len(Error_cases):
                    print("  🎯 ALL Errors are from duplicate numbers")
                    print("  💡 SOLUTION: Your checker rejects duplicates instead of sorting them")
                    print("     This is now expected and correct for duplicates (should return Error)")
        else:
            print("✅ VALIDATION PASSED: Checker correctly identifies unsorted lists as expected (KO or Error)")
            
        return passed, failed, Errors

def main():
    use_pipe_mode = False
    checker_path = "./checker"
    reference_path = "./checker_linux"
    
    # Parse command line arguments
    i = 1
    while i < len(sys.argv):
        arg = sys.argv[i]
        if arg == "--pipe" or arg == "-p":
            use_pipe_mode = True
        elif arg == "--help" or arg == "-h":
            print("Usage: python3 checker_tester.py [options] [checker_path] [reference_path]")
            print("Options:")
            print("  --pipe, -p    Use pipe mode (send empty operations via stdin)")
            print("  --help, -h    Show this help message")
            print("\nExamples:")
            print("  python3 checker_tester.py")
            print("  python3 checker_tester.py --pipe")
            print("  python3 checker_tester.py ./my_checker ./checker_linux")
            print("  python3 checker_tester.py --pipe ./my_checker")
            return
        elif not arg.startswith("--"):
            if checker_path == "./checker":
                checker_path = arg
            elif reference_path == "./checker_linux":
                reference_path = arg
        i += 1
    
    print("Checker Integrity Tester")
    print(f"Testing program: {checker_path}")
    print(f"Reference program: {reference_path}")
    print(f"Mode: {'Pipe mode (empty operations)' if use_pipe_mode else 'Direct mode (EOF signal)'}")
    print()
    
    # Check if programs exist
    if not os.path.exists(checker_path):
        print(f"Warning: Checker program not found at {checker_path}")
        print("Make sure to compile your program first!")
        return
    
    tester = CheckerTester(checker_path, reference_path)
    
    # Generate and run tests
    tester.generate_test_cases(100)
    passed, failed, Errors = tester.run_tests(use_pipe_mode)
    
    # Demonstrate specific examples as requested
    print("\nDEMONSTRATION - Running specific unsorted examples:")
    print("-" * 50)
    
    demo_cases = [
        [3, 1, 2],      # Simple unsorted
        [5, 4, 3, 2, 1], # Reverse sorted
        [1, 3, 2, 4],    # Partially unsorted
        [2, 1],          # Two elements wrong order
        [10, 5, 8, 3, 7, 1, 9, 2, 6, 4],  # Random unsorted
        [2, 1, 3, 10, 10, 5, 4, 10, 5, 5, 1, 10] # Duplicates
    ]
    
    for i, numbers in enumerate(demo_cases, 1):
        if use_pipe_mode:
            output = tester.run_checker_with_pipe(numbers, "", checker_path)
        else:
            output = tester.run_checker(numbers, checker_path)
        is_sorted_val = tester.is_sorted(numbers)
        if len(numbers) != len(set(numbers)):
            expected = "Error"
            correct = output == "Error"
        else:
            expected = "OK" if is_sorted_val else "KO"
            correct = output == expected
        
        print(f"Demo {i}: {numbers}")
        print(f"  Is sorted: {is_sorted_val}")
        print(f"  Expected: {expected}")
        print(f"  Your output: {output}")
        print(f"  Result: {'✅ CORRECT' if correct else '❌ INCORRECT'}")
        print()

if __name__ == "__main__":
    main()