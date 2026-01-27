class SubsetsGenerator:
    def __init__(self, nums):
        self.nums = nums 
    def get_subsets(self):
        result = [[]] 
        for num in self.nums:
            new_subsets = [current + [num] for current in result]
            result.extend(new_subsets) 
        return result
input_list = [4, 5, 6]
generator = SubsetsGenerator(input_list)
subsets = generator.get_subsets()
print(subsets)
