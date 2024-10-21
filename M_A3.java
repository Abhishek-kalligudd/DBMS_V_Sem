//Write a java program to access the given excel file with known file format.
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class ExcelReader {
    public static void main(String[] args) {
        String excelFilePath = "D:\\2SD22CS005\\Minor_3\\Lab_details.xlsx"; // Use double backslashes
        // Or use forward slashes: String excelFilePath = "D:/2SD22CS005/Minor_3/Lab_details.xlsx";
        File file = new File(excelFilePath);

        if (!file.exists()) {
            System.err.println("Error: The file " + excelFilePath + " does not exist.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file);
             Workbook workbook = new XSSFWorkbook(fis)) {

            Sheet sheet = workbook.getSheetAt(0); // Get the first sheet
            if (sheet == null) {
                System.err.println("Error: The sheet at index 0 does not exist.");
                return;
            }

            for (Row row : sheet) {
                for (Cell cell : row) {
                    switch (cell.getCellType()) {
                        case STRING:
                            System.out.print(cell.getStringCellValue() + "\t");
                            break;
                        case NUMERIC:
                            System.out.print(cell.getNumericCellValue() + "\t");
                            break;
                        case BOOLEAN:
                            System.out.print(cell.getBooleanCellValue() + "\t");
                            break;
                        default:
                            System.out.print("Unknown Cell Type\t");
                    }
                }
                System.out.println();
            }
        } catch (IOException e) {
            System.err.println("Error reading the Excel file: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("An unexpected error occurred: " + e.getMessage());
        }
    }
}
