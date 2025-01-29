# Bulk Candy Price Calculator

This program calculates candy prices using real-time market data and bulk discounts. It retrieves the latest prices via an API or defaults to $1.99 per unit if unavailable. A 7% sales tax is applied. I would recommend using Zylalabs API since it has a free trial.

- **Real-Time Pricing**: Fetches prices from an API with a fallback option.
- **Bulk Discounts**: Applies tiered discounts for larger orders.
- **Tax Calculation**: Automatically includes a 7% tax.
- **Input Validation**: Ensures numeric and positive values.

## Example Usage
```
Enter the number of chocolate bars: 200
Fetching real-time chocolate prices...
Price per bar: $1.75
Total price (including tax): $319.45

```

